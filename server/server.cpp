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



/*
accepts connections from player clients and communicates with them
*/
void server(std::vector<std::shared_ptr<PlayerClient>>& clients, MessageSpool& msg_spool, unsigned short port) {
    using boost::asio::ip::tcp;

    // create a boost io_service object (provides the core functionalities for asynchronous IO)
    boost::asio::io_service io_service;

    // create a tcp connection acceptor object
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

    // create a tcp socket and accept a connection on it
    tcp::socket sock(io_service);
    acceptor.accept(sock);

    // once a connection is accept, create a client object for it and add it to the list of clients
    clients.push_back(std::make_shared<PlayerClient>(std::move(sock), msg_spool));

    // run the asynchronous I/O
    io_service.run();
}
