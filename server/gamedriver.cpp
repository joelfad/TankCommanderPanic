/*
Project:  Tank Commander Panic
File:  gamedriver.cpp
Author:  Leonardo Banderali
Description:  The main game logic driver.
*/

// project headers
#include "playerclientlist.hpp"
#include "gamedriver.hpp"
#include "protocol/actionmessagehandle.hpp"

// c++ standard libraries
#include <chrono>
#include <thread>

/*
runs the game
*/
void game_driver(PlayerSpool& client_spool, int player_count, protocol::MessageSpool& msg_spool) {
    PlayerClientList players;

    // wait for clients to connect
    while (players.size() < player_count) {
        PlayerSpool::maybe_item client = client_spool.get();
        if (client) {
            players.push_back(*client);
            //client->send(); // send welcome message (with player ID etc.)
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // send all players the initial game state and game start messages
    //players.send_all();

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
                // TODO notify all clients of move
                //players.send_all();
                break;
            case protocol::Action::SHOOT :
                // TODO notify all clients of shot
                //players.send_all();
                break;
            case protocol::Action::QUIT :
                players[player_id]->disconnect();
                players.erase(player_id);
                if (players.size() == 1) {
                    // TODO send win message
                    //players.back()->send();
                }
                else if (players.size() > 1) {
                    // TODO notify all clients of update
                    //players.send_all();
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
