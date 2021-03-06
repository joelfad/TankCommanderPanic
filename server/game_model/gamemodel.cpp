/*
 * Project: Tank Commander Panic
 * File: gamemodel.cpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

// c++ standard libraries
#include <iostream>
#include <fstream>
#include <vector>

// project headers
#include "gamemodel.hpp"
#include "tankpiece.hpp"
#include "gamemodelerror.hpp"
#include "../messageenvelope.hpp"
#include "../protocol/eventmessagehandle.hpp"
#include "../protocol/createpiecemessagehandle.hpp"

// debug flag
#define DEBUG

game_model::GameModel::GameModel(std::string map_file_path) {
#ifdef DEBUG
    std::cerr << "map file '" << map_file_path << "'...";
#endif

    // open the .map file
    std::ifstream map_file(map_file_path);
    if (map_file.is_open()) {
#ifdef DEBUG
        std::cerr << "opened successfully" << std::endl;
#endif

        // collect basic info
        int map_id_tmp, map_version_tmp;
        map_file >> this->map_name;     // map name
        map_file >> map_id_tmp;         // map id
        this->map_id = static_cast<protocol::MapID>(map_id_tmp);
        map_file >> map_version_tmp;    // map version
        this->map_version = static_cast<protocol::MapID>(map_version_tmp);
        map_file >> this->player_count; // player count
        map_file >> this->map_width;    // map width
        map_file >> this->map_height;   // map height
#ifdef DEBUG
        std::cerr << "map name:     " << this->map_name << std::endl;
        std::cerr << "map id:       " << static_cast<int>(this->map_id) << std::endl;
        std::cerr << "map version:  " << static_cast<int>(this->map_version) << std::endl;
        std::cerr << "player count: " << this->player_count << std::endl;
        std::cerr << "map width:    " << this->map_width << std::endl;
        std::cerr << "map height:   " << this->map_height << std::endl;
#endif

        // create game players
        for (int i = 0; i < this->player_count; i++) {
            auto player = GamePlayer::make_game_player();
#ifdef DEBUG
            std::cerr << "new player " << player.get_id() << "; i = " << i << std::endl;
#endif
            this->players.insert(std::make_pair(player.get_id(), std::move(player)));
        }
#ifdef DEBUG
        for (auto& player: this->players) {
            std::cerr << "player " << player.second.get_id() << std::endl;
        }
#endif

        // resize 2D map vectors
        this->map.resize(this->map_height);
        for (auto& row : this->map) {
            row.resize(this->map_width);
        }
        this->pieces.resize(this->map_height);
        for (auto& row : this->pieces) {
            row.resize(this->map_width);
        }
#ifdef DEBUG
        std::cerr << "map" << this->map.size() << ", " << this->map.at(0).size() << std::endl;
        std::cerr << "pieces" << this->pieces.size() << ", " << this->pieces.at(0).size() << std::endl;
#endif

        // collect player's starting positions
        for (auto& player_pair: this->players) {
            auto& player = player_pair.second;

            // coordinates for the player's three tanks
            int t1x, t1y, t2x, t2y, t3x, t3y;

            // capture the line
            std::string line;
            map_file >> line;
#ifdef DEBUG
            std::cerr << "tank coordinate line '" << line << "'" << std::endl;
#endif

            // collect the coordinates
            std::sscanf(line.c_str(), "%d,%d;%d,%d;%d,%d", &t1x, &t1y, &t2x, &t2y, &t3x, &t3y);
#ifdef DEBUG
            std::cerr << "player " << player.get_id() << " tank coordinates " << t1x << "," << t1y << "\t" << t2x <<
            "," << t2y <<
            "\t" << t3x << "," << t3y << std::endl;
#endif

            // create tanks at the coordinates // TODO make them not all commanders
            this->pieces.at(t1y).at(t1x) = std::make_unique<TankPiece>(player,
                                                                       protocol::TankModel::COMMANDER);
            this->pieces.at(t2y).at(t2x) = std::make_unique<TankPiece>(player,
                                                                       protocol::TankModel::INTERCEPTOR);
            this->pieces.at(t3y).at(t3x) = std::make_unique<TankPiece>(player,
                                                                       protocol::TankModel::ELIMINATOR);
            player.add_tank_id(this->pieces.at(t1y).at(t1x)->get_id());
            player.add_tank_id(this->pieces.at(t2y).at(t2x)->get_id());
            player.add_tank_id(this->pieces.at(t3y).at(t3x)->get_id());
#ifdef DEBUG
            std::cerr << "tank " << this->pieces.at(t1y).at(t1x)->get_id() << std::endl;
            std::cerr << "tank " << this->pieces.at(t2y).at(t2x)->get_id() << std::endl;
            std::cerr << "tank " << this->pieces.at(t3y).at(t3x)->get_id() << std::endl;
#endif
        }

        // collect tile properties and build map
        for (auto& row : this->map) {
            for (auto& tile : row) {
                char t;
                map_file >> t;
                tile = std::make_unique<Tile>(t);
            }
        }
#ifdef DEBUG
        for (auto& row : this->map) {
            for (auto& tile : row) {
                std::cerr << tile->is_clear_drive();
            }
            std::cerr << std::endl;
        }
#endif

        // close the file
        map_file.close();

    } else {

        // file is not opened
        // TODO fail appropriately
    }
}

std::vector<MessageEnvelope> game_model::GameModel::attempt_to_move(protocol::PieceID piece_id,
                                                                    protocol::Direction direction) {

    // list of messages to send
    std::vector<MessageEnvelope> to_send;

    // get coordinates of the tank
    protocol::CoordinateX x;
    protocol::CoordinateY y;
    game_piece_coordinates(piece_id, x, y);

    // check that the piece is a tank
    auto type = this->pieces.at(y).at(x)->get_piece_type();
    if (type < protocol::PieceType::RED_COMMANDER || type > protocol::PieceType::GREEN_NEGOTIATOR) {
        std::cerr << "ERROR: non-tank gamepiece tried to move." << std::endl;
        return to_send;
    }

    // TODO check that the player owns the tank

    // get target coordinates
    protocol::CoordinateX to_x = x;
    protocol::CoordinateY to_y = y;
    switch (direction) {
        case protocol::Direction::NORTH :
            to_y--;
            break;
        case protocol::Direction::EAST :
            to_x++;
            break;
        case protocol::Direction::SOUTH :
            to_y++;
            break;
        case protocol::Direction::WEST :
            to_x--;
            break;
        default:
            break;
    }

    // move distance
    int distance = 0;

    // check the map tile at the target coordinates
    if (this->map.at(to_y).at(to_x)->is_clear_drive()) {

        // check the location for solid game pieces
        if (!this->pieces.at(to_y).at(to_x) || this->pieces.at(to_y).at(to_x)->is_clear_drive()) {

            // set the distance
            distance = 1;

            // move the game piece_id
            this->pieces.at(to_y).at(to_x) = std::move(this->pieces.at(y).at(x));

#ifdef DEBUG
            std::cerr << "Tank " << piece_id << " moved from (" << (int) x << "," << (int) y << ") to (" << (int) to_x
            << "," << (int) to_y << ")." << std::endl;
#endif

            // TODO check for pickup items
        }
    }

    // compose move message
    auto move_message = protocol::EventMessageHandle();
    move_message.event_type(protocol::EventType::MOVE_GAME_PIECE);
    move_message.direction(direction);
    move_message.value(distance);
    move_message.piece_id(piece_id);
#ifdef DEBUG
    std::cerr << "[Sent] Event Message" << std::endl;
    std::cerr << "  event type: " << static_cast<int>(protocol::EventType::MOVE_GAME_PIECE) << std::endl;
    std::cerr << "  direction:  " << static_cast<int>(direction) << std::endl;
    std::cerr << "  value:      " << distance << std::endl;
    std::cerr << "  piece id:   " << static_cast<int>(piece_id) << std::endl << std::endl;
#endif
    to_send.push_back(MessageEnvelope(Recipient::ALL, move_message.to_msg()));

    return to_send;
}

std::vector<MessageEnvelope> game_model::GameModel::attempt_to_shoot(protocol::PieceID piece_id,
                                                                     protocol::Direction direction,
                                                                     protocol::PlayerID player_id) {

    // list of messages to send
    std::vector<MessageEnvelope> to_send;

    // get reference to player
    GamePlayer& player = this->players[player_id];

#ifdef DEBUG
    std::cerr << "player id: " << player.get_id() << std::endl;
    std::cerr << "ammo:      " << player.get_ammo() << std::endl;
#endif

    // check that the player has ammo
    if (player.get_ammo() <= 0)
        return to_send;

#ifdef DEBUG
    std::cerr << "enough ammo!" << std::endl;
#endif

    // use up an ammo
    player.change_ammo(-1);

    // get coordinates of the tank
    protocol::CoordinateX x;
    protocol::CoordinateY y;
    game_piece_coordinates(piece_id, x, y);

#ifdef DEBUG
    std::cerr << "tank at (" << x << "," << y << ")" << std::endl;
#endif

    // check that the piece is a tank
    auto type = this->pieces.at(y).at(x)->get_piece_type();
#ifdef DEBUG
    std::cerr << "type: " << static_cast<int>(type) << std::endl;
#endif
    if (type < protocol::PieceType::RED_COMMANDER || type > protocol::PieceType::GREEN_NEGOTIATOR) {
        std::cerr << "ERROR: non-tank gamepiece tried to shoot." << std::endl;
        return to_send;
    }

    // TODO check that the player owns the tank

    // get range of the tank
    auto model = protocol::tank_model(type);
    auto range = TankPiece::get_range(model);

    // get power of the tank
    auto power = TankPiece::get_power(model);

    // find landing zone
    protocol::CoordinateX to_x = x;
    protocol::CoordinateY to_y = y;
    for (int i = 0; i < range; i++) {
        switch (direction) {
            case protocol::Direction::NORTH :
                to_y--;
                break;
            case protocol::Direction::EAST :
                to_x++;
                break;
            case protocol::Direction::SOUTH :
                to_y++;
                break;
            case protocol::Direction::WEST :
                to_x--;
                break;
            default:
                break;
        }

        // check the target coordinates for solid map tiles and game pieces
        if (!this->map.at(to_y).at(to_x)->is_clear_shot() ||
            (this->pieces.at(to_y).at(to_x) && !this->pieces.at(to_y).at(to_x)->is_clear_shot())) {
            // HIT SOMETHING!
            break;
        }
    }

#ifdef DEBUG
    std::cerr << "Tank " << piece_id << " fired from (" << (int) x << "," << (int) y << ") at (" << (int) to_x << "," <<
    (int) to_y << ")." << std::endl;
#endif

    // compose move message -- so tank point in the correct direction on everyone's screen
    auto move_message = protocol::EventMessageHandle();
    move_message.event_type(protocol::EventType::MOVE_GAME_PIECE);
    move_message.direction(direction);
    move_message.value(0);
    move_message.piece_id(piece_id);
#ifdef DEBUG
    std::cerr << "[Sent] Event Message" << std::endl;
    std::cerr << "  event type: " << static_cast<int>(protocol::EventType::MOVE_GAME_PIECE) << std::endl;
    std::cerr << "  direction:  " << static_cast<int>(direction) << std::endl;
    std::cerr << "  value:      0" << std::endl;
    std::cerr << "  piece id:   " << static_cast<int>(piece_id) << std::endl << std::endl;
#endif
    to_send.push_back(MessageEnvelope(Recipient::ALL, move_message.to_msg()));

    // compose ammo message -- sent only to the shooter (actor)
    auto ammo_message = protocol::EventMessageHandle();
    ammo_message.event_type(protocol::EventType::UPDATE_AMMO);
    ammo_message.direction(protocol::Direction::NONE);
    ammo_message.value(player.get_ammo());
    ammo_message.piece_id(0);
#ifdef DEBUG
    std::cerr << "[Sent] Event Message" << std::endl;
    std::cerr << "  event type: " << static_cast<int>(protocol::EventType::UPDATE_AMMO) << std::endl;
    std::cerr << "  direction:  " << static_cast<int>(protocol::Direction::NONE) << std::endl;
    std::cerr << "  value:      " << player.get_ammo() << std::endl;
    std::cerr << "  piece id:   0" << std::endl << std::endl;
#endif
    to_send.push_back(MessageEnvelope(Recipient::ACTOR, ammo_message.to_msg()));

    // check the hit location for solid game pieces
    if (this->pieces.at(to_y).at(to_x) && !this->pieces.at(to_y).at(to_x)->is_clear_shot()) {

        // get the target
        auto target_ptr = dynamic_cast<SolidPiece *>(this->pieces.at(to_y).at(to_x).get());
        if (target_ptr) {

            // damage the target
            target_ptr->shot(power);

            // id of target piece
            auto target_id = target_ptr->get_id();

            // check if the target was destroyed
            if (target_ptr->get_health() <= 0) {

                // compose destroy message
                auto destroy_message = protocol::EventMessageHandle();
                destroy_message.event_type(protocol::EventType::DESTROY_GAME_PIECE);
                destroy_message.direction(protocol::Direction::NONE);
                destroy_message.value(0);
                destroy_message.piece_id(target_id);
#ifdef DEBUG
                std::cerr << "[Sent] Event Message" << std::endl;
                std::cerr << "  event type: " << static_cast<int>(protocol::EventType::DESTROY_GAME_PIECE) << std::endl;
                std::cerr << "  direction:  " << static_cast<int>(protocol::Direction::NONE) << std::endl;
                std::cerr << "  value:      0" << std::endl;
                std::cerr << "  piece id:   " << static_cast<int>(target_id) << std::endl << std::endl;
#endif
                to_send.push_back(MessageEnvelope(Recipient::ALL, destroy_message.to_msg()));

                // check if target is a tank
                auto tank_ptr = dynamic_cast<TankPiece *>(target_ptr);
                if (tank_ptr) {

                    // get tank id
                    auto tank_id = tank_ptr->get_id();

                    // get tank's commander
                    auto& commander = tank_ptr->get_commander();

#ifdef DEBUG
                    std::cerr << "a tank was lost by player " << commander.get_id() << std::endl;
#endif

                    // player looses the tank
                    commander.loose_tank(tank_id);
#ifdef DEBUG
                    std::cerr << "player " << commander.get_id() << " has " <<
                    static_cast<int>(commander.get_tank_count()) << " tanks" << std::endl;
#endif

                    // check if commander lost
                    if (commander.get_tank_count() <= 0) {

                        // compose game over message
                        auto game_over_message = protocol::EventMessageHandle();
                        game_over_message.event_type(protocol::EventType::GAME_OVER);
                        game_over_message.direction(protocol::Direction::NONE);
                        game_over_message.value(protocol::EndGameState::LOSE);
                        game_over_message.piece_id(0);
#ifdef DEBUG
                        std::cerr << "[Sent] Event Message" << std::endl;
                        std::cerr << "  event type: " << static_cast<int>(protocol::EventType::GAME_OVER) << std::endl;
                        std::cerr << "  direction:  " << static_cast<int>(protocol::Direction::NONE) << std::endl;
                        std::cerr << "  value:      " << static_cast<int>(protocol::EndGameState::LOSE) << std::endl;
                        std::cerr << "  piece id:   0" << std::endl << std::endl;
#endif
                        to_send.push_back(
                                MessageEnvelope(Recipient::TARGET, commander.get_id(), game_over_message.to_msg()));

                        // register a player loss
                        this->players.erase(commander.get_id());

                        // check if actor won
                        if (this->players.size() <= 1) {
                            // compose win game message
                            auto win_game_message = protocol::EventMessageHandle();
                            win_game_message.event_type(protocol::EventType::GAME_OVER);
                            win_game_message.direction(protocol::Direction::NONE);
                            win_game_message.value(protocol::EndGameState::WIN);
                            win_game_message.piece_id(0);
#ifdef DEBUG
                            std::cerr << "[Sent] Event Message" << std::endl;
                            std::cerr << "  event type: " << static_cast<int>(protocol::EventType::GAME_OVER) <<
                            std::endl;
                            std::cerr << "  direction:  " << static_cast<int>(protocol::Direction::NONE) << std::endl;
                            std::cerr << "  value:      " << static_cast<int>(protocol::EndGameState::WIN) << std::endl;
                            std::cerr << "  piece id:   0" << std::endl << std::endl;
#endif
                            to_send.push_back(MessageEnvelope(Recipient::ACTOR, win_game_message.to_msg()));
                        }
                    }
                }

                // delete the destroyed target
                this->pieces.at(to_y).at(to_x).reset();
            } else {

                // compose damage message
                auto damage_message = protocol::EventMessageHandle();
                damage_message.event_type(protocol::EventType::UPDATE_HEALTH);
                damage_message.direction(protocol::Direction::NONE);
                damage_message.value(target_ptr->get_health());
                damage_message.piece_id(target_id);
#ifdef DEBUG
                std::cerr << "[Sent] Event Message" << std::endl;
                std::cerr << "  event type: " << static_cast<int>(protocol::EventType::UPDATE_HEALTH) << std::endl;
                std::cerr << "  direction:  " << static_cast<int>(protocol::Direction::NONE) << std::endl;
                std::cerr << "  value:      " << target_ptr->get_health() << std::endl;
                std::cerr << "  piece id:   " << static_cast<int>(target_id) << std::endl << std::endl;
#endif
                to_send.push_back(MessageEnvelope(Recipient::ALL, damage_message.to_msg()));
            }
        }
    }

    return to_send;
}

void game_model::GameModel::game_piece_coordinates(protocol::PieceID id, protocol::CoordinateX& x,
                                                   protocol::CoordinateY& y) {
    for (y = 0; y < this->pieces.size(); y++) {
        for (x = 0; x < this->pieces.at(y).size(); x++) {
            if (this->pieces.at(y).at(x) && this->pieces.at(y).at(x)->get_id() == id)
                return;
        }
    }
    throw GamePieceNotFoundError(std::string("game piece with id ").append(std::to_string(id)).append(" not found"));
}

std::vector<MessageEnvelope> game_model::GameModel::create_all_pieces() {
    auto to_send = std::vector<MessageEnvelope>();
    for (int y = 0; y < this->pieces.size(); y++) {
        for (int x = 0; x < this->pieces.at(y).size(); x++) {
            if (this->pieces.at(y).at(x)) {

                // get piece pointer
                auto piece_ptr = static_cast<GamePiece *>(this->pieces.at(y).at(x).get());

                // declare value
                int value = 0;

                // check if piece is a solid piece
                auto solid_ptr = static_cast<TankPiece *>(this->pieces.at(y).at(x).get());
                if (solid_ptr) {
                    value = solid_ptr->get_health();
                }

                // TODO check if piece is other piece types (as they are implemented)

                // compose create piece message
                auto create_piece_message = protocol::CreatePieceMessageHandle();
                create_piece_message.piece_type(piece_ptr->get_piece_type());
                create_piece_message.value(value);
                create_piece_message.piece_id(piece_ptr->get_id());
                create_piece_message.piece_coord_x(x);
                create_piece_message.piece_coord_y(y);
#ifdef DEBUG
                std::cerr << "[Sent] Create Piece Message" << std::endl;
                std::cerr << "  piece type: " << static_cast<int>(piece_ptr->get_piece_type()) << std::endl;
                std::cerr << "  value:      " << value << std::endl;
                std::cerr << "  piece id:   " << static_cast<int>(piece_ptr->get_id()) << std::endl;
                std::cerr << "  coord x:    " << x << std::endl;
                std::cerr << "  coord y:    " << y << std::endl << std::endl;
#endif
                to_send.push_back(MessageEnvelope(Recipient::ALL, create_piece_message.to_msg()));
            }
        }
    }
    return to_send;
}
