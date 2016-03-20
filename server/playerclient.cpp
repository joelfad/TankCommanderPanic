/*
Project:  Tank Commander Panic
File:  playerclient.cpp
Author:  Leonardo Banderali
Description:  This class handles asynchronous communication with a client/player.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

// project headers
#include "playerclient.hpp"
#include <iostream>


//~constructors~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PlayerClient::PlayerClient(boost::asio::ip::tcp::socket _socket, protocol::MessageSpool& _receive_msg_spool)
: socket{std::move(_socket)}, receive_msg_spool{_receive_msg_spool} {}

/*
starts the server
*/
void PlayerClient::start() {
    read();
}



//~public functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
adds message to buffer and performs asynchronous write
*/
void PlayerClient::send(std::string msg) {
    /*#################################################################################
    ### This function does not perform the actual write (send) operation. Instead,   ##
    ### it adds the new message to the spool of messages to be written, letting      ##
    ### `PlayerClient::write()` performs the asynchronous write operation.           ##
    ###                                                                              ##
    ### By design, `PlayerClient::write()` will ensure that messages continue to be  ##
    ### written until there are no more buffers to write (`send_buffers` is empty).  ##
    ### So, if there already are buffers to be sent before the new buffer is added,  ##
    ### then there must be asynchronous writes underway which will eventually        ##
    ### consume the newly added buffer. However, if there are no unwritten buffers,  ##
    ### then there cannot be any asynchronous writes underway (there is nothing to   ##
    ### write/send). So, an asynchronous write must be started.                      ##
    ###                                                                              ##
    ### Because two threads can concurently access the message spool, it is possible ##
    ### for a race condition to occure. For exampel, if while a thread is executing  ##
    ### this function, an asynchronous write occures in another thread. Suppose that ##
    ### there is initially one unsent messages in the spool. A thread executing      ##
    ### this function sees that the spool is not empty and therefor decides that,    ##
    ### there must be some asynchronous writes still happening. However, before the  ##
    ### thread is able to reach the `if` statement, an asynchronous write occures on ##
    ### another thread that removes the message from the spool. Now, the spool is    ##
    ### empty and the asynchronous writes have ended. But, the thread executing this ##
    ### function still "thinks" that there is an unsent message and that the         ##
    ### asynchronous writes have not ended. So, it does not start a new asynchronous ##
    ### write. As a result, the newly added message stays in the spool and does not  ##
    ### get sent (yet).                                                              ##
    ###                                                                              ##
    ### To avoid this problem, a mutex is used for thread synchronization. For       ##
    ### simplicity, the entire function body is treaded as the critical zone.        ##
    #################################################################################*/

    //spool_lock.lock();  //*** begin cirical zone ***
    std::lock_guard<std::mutex> lock{spool_lock};

    bool not_writing = write_msg_spool.empty(); // check if there are current asynchronous write
    write_msg_spool.push_back(msg);             // add new message buffer
    if (not_writing) {                          // if there are no asynchronous writes, do a new write
        write();
    }

    //spool_lock.unlock();//*** end cirical zone ***
}



//~private functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
performs asynchronous read on the socket
*/
void PlayerClient::read() {
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(read_buffer.data(), read_buffer.size()),
        [this, self](boost::system::error_code error, std::size_t /*length*/) {
            if (!error) {
                auto msg = std::string(read_buffer.data());
                receive_msg_spool.add(msg);
            }
            read();
        }
    );
}

/*
performs asynchronous write on the socket
*/
void PlayerClient::write() {
    auto self(shared_from_this());
    boost::asio::async_write(socket, boost::asio::buffer(write_msg_spool.front().data(), write_msg_spool.front().length()),
        [this, self](boost::system::error_code /*error*/, std::size_t /*transmitted*/) {
            /*#########################################################################################
            ### This function will be called once the asynchronous write is complete.                ##
            ###                                                                                      ##
            ### Since the message has been sent, it can be removed from the spool.                   ##
            ###                                                                                      ##
            ### A mutex is used to avoid race conditions with `PlayerClient::send(std::string msg)`. ##
            ########################################################################################*/

            //spool_lock.lock();  //*** begin cirical zone ***
            std::lock_guard<std::mutex> lock{spool_lock};

            write_msg_spool.pop_front();    // remove the message from the spool

            if (!write_msg_spool.empty()) { // if there are more unwritten/unsent messages
                write();                    // do another asynchronous write
            }

            //spool_lock.unlock();//*** end cirical zone ***
        });
}
