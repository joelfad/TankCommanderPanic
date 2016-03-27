/*
Project:  Tank Commander Panic
File:  gamedriver.cpp
Author:  Leonardo Banderali
Description:  The main game logic driver.
*/

// project headers
#include "gamedriver.hpp"
#include "actionmessagehandle.hpp"

// c++ standard libraries
#include <chrono>
#include <thread>

/*
runs the game
*/
void game_driver(PlayerSpool& client_spool, protocol::MessageSpool& msg_spool) {
    PlayerClientList players;

    // wait for 2 clients to connect
    while (players.size() < 2) {
        PlayerSpool::maybe_item client = client_spool.get();
        if (client) {
            players.push_back(*client);
            //client->send(); // send welcome message (with player ID etc.)
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // send all players the initial game state and game start messages
    //for (auto&& player : players) {
    //    player->send();
    //}

    // run the game
    while (true) {
        // get next player message
        protocol::MessageSpool::maybe_item message = msg_spool.get();

        // process the message and update clients
        if (message) {
            // process message
            auto action = protocol::ActionMessageHandle::make_from_msg(*message);
            auto player_id = action.player();

            // perfrom action
            switch (action.action()) {
            case protocol::Action::MOVE :
                // notify all clients of move
                //for (auto&& player : players) {
                //    player->send();
                //}
                break;
            case protocol::Action::SHOOT :
                // notify all clients of shot
                //for (auto&& player : players) {
                //    player->send();
                //}
                break;
            case protocol::Action::QUIT :
                //players[player_id]->disconnect();
                players.erase(players.cbegin() + player_id);
                if (players.size() == 1) {
                    // send win message
                    //players.back()->send();
                }
                else if (players.size() > 1) {
                    // notify all clients of update
                    //for (auto&& player : players) {
                    //    player->send();
                    //}
                }
                break;
            default:
                break;
            }
        }

        // wait for next game tick
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
