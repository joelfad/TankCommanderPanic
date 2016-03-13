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
                        //clients.push_back(c);
                        //waiting_clients.push_back(c);
                        client_spool.add(c);
                        //if (waiting_clients.size() == 2)
                            //client_spool.add(std::move(waiting_clients));
                    }

                    do_accept();
                });
        }

        tcp::acceptor acceptor;
        tcp::socket socket;

        //PlayerClientList waiting_clients;   // clients that are waiting for more players to connect to play a game
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
    //tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
    auto acceptor = ConnectionAcceptor{io_service, port, client_spool, msg_spool};

    // create a tcp socket
    /*tcp::socket sock(io_service);

    // accept two connections
    for (int i = 0; i < 2; i++) {
        // once a connection is accept, create a client object for it and add it to the list of clients
        acceptor.accept(sock);
        auto c = std::make_shared<PlayerClient>(std::move(sock), msg_spool);
        c->start();
        clients.push_back(c);
    }*/

    // run the asynchronous I/O
    io_service.run();
}
