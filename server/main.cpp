/*
Project:  Tank Commander Panic
File:  main.cpp
Author:  Leonardo Banderali
Description:  This is a simple TCP/UDP echoing server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
//#include "simple_servers.hpp"
//#include "async_tcp.hpp"
//#include "async_udp.hpp"
#include "server.hpp"
#include "gamedriver.hpp"
#include "playerclient.hpp"
#include "messagespool.hpp"

// c++ standard libraries
#include <exception>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

// boost libraries
//#include <boost/asio.hpp>



//~main program~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) {

    // validate the argument count
    if (argc != 2) {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }

    try
    {
        // create a boost io_service object (provides the core functionalities for asynchronous IO)
        //boost::asio::io_service io_service;

        // start the server
        //simple_tcp_server(io_service, std::atoi(argv[1]));
        //simple_udp_server(io_service, std::atoi(argv[1]));

        // create asynchronous server objects
        //async_tcp_server s_tcp(io_service, std::atoi(argv[1]));
        //async_udp_server s_udp(io_service, std::atoi(argv[1]));

        //io_service.run();

        std::vector<std::shared_ptr<PlayerClient>> players;
        MessageSpool messages;

        // run the communication server on a separate thread
        std::thread com_server([&](){
            server(players, messages, std::atoi(argv[1]));
        });

        // run the game
        game_driver(players, messages);

        // wait for communication to finish
        com_server.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
