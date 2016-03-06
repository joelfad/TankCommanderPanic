/*
Project:  Tank Commander Panic
File:  playerclient.hpp
Author:  Leonardo Banderali
Description:  This class handles asynchronous communication with a client/player.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#ifndef PLAYERCLIENT_HPP
#define PLAYERCLIENT_HPP



// c++ standard libraries
#include <deque>
#include <mutex>

// boost libraries
#include <boost/asio.hpp>



class PlayerClient : public std::enable_shared_from_this<PlayerClient> {
    public:
        explicit PlayerClient(boost::asio::ip::tcp::socket _socket);

        void send(std::string msg);
        /*  adds message to buffer and performs asynchronous write */

    private:

        void read();
        /*  performs asynchronous read on the socket */

        void write();
        /*  performs asynchronous write on the socket */

        boost::asio::ip::tcp::socket socket;        // the communication socket
        std::deque<std::string> write_msg_spool;    // spool of messages (data buffers) to be written/sent
        std::mutex spool_lock;                      // a mutex to prevent race condition with data buffers
};

#endif // PLAYERCLIENT_HPP
