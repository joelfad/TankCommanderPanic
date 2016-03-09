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
void game_driver(std::vector<std::shared_ptr<PlayerClient>>& clients, MessageSpool& msg_spool) {
    while (true) {
        for (auto&& client : clients) {
            client->send("Message!");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}