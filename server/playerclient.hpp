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



// project headers
#include "protocol/message.hpp"

// c++ standard libraries
#include <deque>
#include <mutex>
#include <memory>
#include <vector>

// boost libraries
#include <boost/asio.hpp>



class PlayerClient : public std::enable_shared_from_this<PlayerClient> {
    public:
        using Ptr = std::shared_ptr<PlayerClient>;

        PlayerClient(boost::asio::ip::tcp::socket _socket, protocol::MessageSpool& _receive_msg_spool);

        void send(protocol::Message msg);
        /*  adds message to buffer and performs asynchronous write */

        void start();
        /*  starts the server */

        void disconnect();
        /*  closes the connection to the client; all async operations are cancelled */

    private:

        void read();
        /*  performs asynchronous read on the socket */

        void write();
        /*  performs asynchronous write on the socket */

        boost::asio::ip::tcp::socket socket;            // the communication socket

        protocol::MessageSpool& receive_msg_spool;      // spool for the messages recieved
        std::array<unsigned char, 16> read_buffer;      // buffer in which to read messages

        std::deque<protocol::Message> write_msg_spool;  // spool of messages (data buffers) to be written/sent
        std::mutex spool_lock;                          // a mutex to prevent race condition with data buffers
};

using PlayerSpool = spool<PlayerClient::Ptr>;

#endif // PLAYERCLIENT_HPP
