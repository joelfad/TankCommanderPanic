/*
Project:  Tank Commander Panic
File:  main.cpp
Author:  Leonardo Banderali
Description:  This is the server for the Tank Commander Panic game.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
#include "server.hpp"
#include "gamedriver.hpp"
#include "playerclient.hpp"
#include "protocol/message.hpp"
#include "game_model/gamemodel.hpp"

// c++ standard libraries
#include <thread>
#include <iostream>
#include <functional>



//~main program~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) {

    // validate the argument count
    if (argc != 2) {
        std::cerr << "Usage: server <STAGE NAME>\n";
        return 1;
    }

    game_model::GameModel model(argv[1]);

    PlayerSpool players;
    protocol::MessageSpool messages;

    // TODO helpfully print this server's public IP to the screen

    // run the communication server on a separate thread
    auto com_server = std::thread{server, std::ref(players), std::ref(messages), 4410};

    // run instance of the game
    // TODO pass expected player count as argument
    game_driver(players, messages);

    // wait for communication to finish
    com_server.join();
}
