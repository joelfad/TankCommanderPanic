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
#include "game_model/gamemodel.hpp"

// c++ standard libraries
#include <chrono>
#include <thread>
#include <iostream>

#define DEBUG

/*
runs the game
*/
void game_driver(PlayerSpool& client_spool, std::string map_file_path, protocol::MessageSpool& msg_spool) {

    // initialize game model
    game_model::GameModel model(map_file_path);
#ifdef DEBUG
    std::cerr << "game model initialized" << std::endl;
#endif

    PlayerClientList players;

    // wait for clients to connect
    while (players.size() < model.get_player_count()) {
        PlayerSpool::maybe_item client = client_spool.get();
        if (client) {
            players.push_back(*client);
            //client->send(); // TODO send welcome message (with player ID etc.)
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // TODO send all players the initial game state and game start messages
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

#ifdef DEBUG
            std::cerr << "Message Recieved" << std::endl;
            std::cerr << "  player:    " << action.player() << std::endl;
            std::cerr << "  action:    " << static_cast<int>(action.action()) << std::endl;
            std::cerr << "  direction: " << static_cast<int>(action.direction()) << std::endl;
            std::cerr << "  piece id:  " << action.piece() << std::endl << std::endl;
#endif

            // perform action
            switch (action.action()) {
            case protocol::Action::MOVE :
                model.attempt_to_move(action.piece(), action.direction());
                // TODO notify all clients of move
                //players.send_all();
                break;
            case protocol::Action::SHOOT :
                model.attempt_to_shoot(action.piece(), action.direction(), action.player());
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
