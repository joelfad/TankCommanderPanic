/*
Project:  Tank Commander Panic
File:  gamedriver.cpp
Author:  Leonardo Banderali
Description:  The main game logic driver.
*/

// project headers
#include "playerclientlist.hpp"
#include "gamedriver.hpp"
#include "messageenvelope.hpp"
#include "protocol/actionmessagehandle.hpp"
#include "game_model/gamemodel.hpp"
#include "protocol/eventmessagehandle.hpp"

// c++ standard libraries
#include <chrono>
#include <thread>
#include <iostream>

#define DEBUG

void send_envelopes(std::vector<MessageEnvelope> to_send, PlayerClientList& players, protocol::PlayerID actor);

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
    auto game_player = model.get_players().cbegin();
    while (true) {
        PlayerSpool::maybe_item client = client_spool.get();
        if (client) {
            players.push_back(game_player->second.get_id(), *client);
            //client->send(); // TODO send welcome message (with player ID etc.)
            game_player++;
            if (game_player == model.get_players().cend()) break;
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
            std::cerr << "[Received] Action Message" << std::endl;
            std::cerr << "  player:    " << action.player() << std::endl;
            std::cerr << "  action:    " << static_cast<int>(action.action()) << std::endl;
            std::cerr << "  direction: " << static_cast<int>(action.direction()) << std::endl;
            std::cerr << "  piece id:  " << action.piece() << std::endl << std::endl;
#endif

            // list of messages to send
            std::vector<MessageEnvelope> to_send;

            // perform action
            switch (action.action()) {
                case protocol::Action::MOVE :

                    // attempt move in the model
                    to_send = model.attempt_to_move(action.piece(), action.direction());

                    // notify all clients of move
                    send_envelopes(to_send, players, player_id);

                    break;
                case protocol::Action::SHOOT :

                    // attempt shot in the model
                    to_send = model.attempt_to_shoot(action.piece(), action.direction(), action.player());

                    // notify all clients of shot
                    send_envelopes(to_send, players, player_id);

                    break;
                case protocol::Action::QUIT :
                    players[player_id]->disconnect();
                    players.erase(player_id);
                    if (players.size() == 1) {
                        // TODO send win message
                        protocol::EventMessageHandle win_msg;
                        win_msg.event_type(protocol::EventType::GAME_OVER);
                        win_msg.value(protocol::EndGameState::WIN);
#ifdef DEBUG
                        std::cerr << "[Sent] Event Message" << std::endl;
                        std::cerr << "  event type: " << static_cast<int>(protocol::EventType::GAME_OVER) << std::endl;
                        std::cerr << "  direction:  0" << std::endl;
                        std::cerr << "  value:      " << static_cast<int>(protocol::EndGameState::WIN)<< std::endl;
                        std::cerr << "  piece id:   0" << std::endl;
#endif
                        players.begin()->second->send(win_msg.to_msg());
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

void send_envelopes(std::vector<MessageEnvelope> to_send, PlayerClientList& players, protocol::PlayerID actor) {

    for (auto& envelope: to_send) {
        switch (envelope.get_recipient()) {
            case Recipient::ALL :
                players.send_all(envelope.get_message());
                break;
            case Recipient::ACTOR :
                // TODO send to correct client
                break;
        }
    }
}
