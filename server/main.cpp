/*
Project:  Tank Commander Panic
File:  main.cpp
Author:  Leonardo Banderali
Description:  This is a simple TCP/UDP echoing server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
#include "server.hpp"
#include "gamedriver.hpp"
#include "playerclient.hpp"
#include "messagespool.hpp"

// c++ standard libraries
#include <exception>
#include <thread>
#include <functional>



//~main program~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) {

    // validate the argument count
    if (argc != 2) {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }

    try {
        //PlayerClientList players;
        PlayerSpool players;
        MessageSpool messages;

        // run the communication server on a separate thread
        /*std::thread com_server([&](){
            server(players, messages, std::atoi(argv[1]));
        });*/
        auto com_server = std::thread{server, std::ref(players), std::ref(messages), std::atoi(argv[1])};
        /*using boost::asio::ip::tcp;

        // create a boost io_service object (provides the core functionalities for asynchronous IO)
        boost::asio::io_service io_service;

        // create a tcp connection acceptor object
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), std::atoi(argv[1])));

        // accept two connections
        for (int i = 0; i < 2; i++) {
            // create a tcp socket
            tcp::socket sock(io_service);

            // once a connection is accept, create a client object for it and add it to the list of clients
            acceptor.accept(sock);
            auto client = std::make_shared<PlayerClient>(std::move(sock), messages);
            client->start();
            players.push_back(client);
        }*/

        // run the game in a separate thread
        //std::thread game([&](){
            game_driver(players, messages);
        //});

        // run the asynchronous I/O
        //io_service.run();

        // wait for communication to finish
        com_server.join();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
