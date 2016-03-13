/*
Project:  Tank Commander Panic
File:  gamedriver.cpp
Author:  Leonardo Banderali
Description:  The main game logic driver.
*/

// project headers
#include "gamedriver.hpp"

// c++ standard libraries
#include <chrono>
#include <thread>

/*
runs the game
*/
void game_driver(PlayerSpool& client_spool, MessageSpool& msg_spool) {
    PlayerClientList players;
    while (true) {
        PlayerSpool::maybe_item client = client_spool.get();
        if (client) {
            players.push_back(*client);
        }

        MessageSpool::maybe_item message = msg_spool.get();
        if (message) {
            for (auto&& player : players) {
                player->send(*message);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
