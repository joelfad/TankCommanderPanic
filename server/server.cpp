/*
Project:  Tank Commander Panic
File:  server.cpp
Author:  Leonardo Banderali
Description:  The games communication server.
*/

// project headers
#include "server.hpp"

// c++ standard libraries
#include <utility>

// boost libraries
#include <boost/asio.hpp>




using boost::asio::ip::tcp;

/*
An asynchronous connection acceptort class
*/
class ConnectionAcceptor {
    public:
        ConnectionAcceptor(boost::asio::io_service& io_service, unsigned short port, PlayerSpool& _client_spool, MessageSpool& _msg_spool)
            : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service), client_spool{_client_spool}, msg_spool{_msg_spool}
        {
            do_accept();
        }

    private:
        void do_accept() {
            acceptor.async_accept(socket,
                [this](boost::system::error_code ec)
                {
                    if (!ec)
                    {
                        auto c = std::make_shared<PlayerClient>(std::move(socket), msg_spool);
                        c->start();
                        client_spool.add(c);
                    }

                    do_accept();
                });
        }

        tcp::acceptor acceptor;
        tcp::socket socket;

        PlayerSpool& client_spool;  // spool for groups of clients to play together
        MessageSpool& msg_spool;    // spool for messages comming from clients
};

/*
accepts connections from player clients and communicates with them
*/
void server(PlayerSpool& client_spool, MessageSpool& msg_spool, unsigned short port) {
    using boost::asio::ip::tcp;

    // create a boost io_service object (provides the core functionalities for asynchronous IO)
    boost::asio::io_service io_service;

    // create a tcp connection acceptor object
    auto acceptor = ConnectionAcceptor{io_service, port, client_spool, msg_spool};


    // run the asynchronous I/O
    io_service.run();
}
