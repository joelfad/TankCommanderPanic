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
#include "message.hpp"

// c++ standard libraries
#include <thread>
#include <iostream>
#include <functional>



//~main program~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) {

    // validate the argument next_id
    if (argc != 2) {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }

    PlayerSpool players;
    protocol::MessageSpool messages;

    // run the communication server on a separate thread
    auto com_server = std::thread{server, std::ref(players), std::ref(messages), std::atoi(argv[1])};

    // run instance of the game
    game_driver(players, messages);

    // wait for communication to finish
    com_server.join();
}
