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
        ConnectionAcceptor(boost::asio::io_service& io_service, unsigned short port, PlayerClientList& _clients, MessageSpool& _msg_spool)
            : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service), clients{_clients}, msg_spool{_msg_spool}
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
                        clients.push_back(c);
                    }

                    //do_accept();
                });
        }

        tcp::acceptor acceptor;
        tcp::socket socket;
        PlayerClientList& clients;
        MessageSpool& msg_spool;
};

/*
accepts connections from player clients and communicates with them
*/
void server(PlayerClientList& clients, MessageSpool& msg_spool, unsigned short port) {
    using boost::asio::ip::tcp;

    // create a boost io_service object (provides the core functionalities for asynchronous IO)
    boost::asio::io_service io_service;

    // create a tcp connection acceptor object
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
    //auto acceptor = ConnectionAcceptor{io_service, port, clients, msg_spool};

    // create a tcp socket and accept a connection on it
    tcp::socket sock(io_service);
    acceptor.accept(sock);

    // once a connection is accept, create a client object for it and add it to the list of clients
    auto c = std::make_shared<PlayerClient>(std::move(sock), msg_spool);
    c->start();
    clients.push_back(c);

    // run the asynchronous I/O
    io_service.run();
}
