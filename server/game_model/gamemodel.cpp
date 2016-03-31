/*
 * Project: Tank Commander Panic
 * File: gamemodel.cpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "gamemodel.hpp"
#include "tankpiece.hpp"

// debug flag
//#define DEBUG

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
        map_file >> this->map_name;     // map name
        map_file >> this->map_id;       // map id
        map_file >> this->map_version;  // map version
        map_file >> this->player_count; // player count
        map_file >> this->map_width;    // map width
        map_file >> this->map_height;   // map height
#ifdef DEBUG
        std::cerr << "map name:     " << this->map_name     << std::endl;
        std::cerr << "map id:       " << this->map_id       << std::endl;
        std::cerr << "map version:  " << this->map_version  << std::endl;
        std::cerr << "player count: " << this->player_count << std::endl;
        std::cerr << "map width:    " << this->map_width    << std::endl;
        std::cerr << "map height:   " << this->map_height   << std::endl;
#endif

        // create game players
        this->players = std::vector<GamePlayer>(static_cast<unsigned long>(this->player_count));
#ifdef DEBUG
        for (GamePlayer player: this->players) {
            std::cerr << "player " << player.get_id() << std::endl;
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
        for (int i = 0; i < this->player_count; i++) {

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
            std::cerr << "player " << i << " tank coordinates " << t1x << "," << t1y << "\t" << t2x << "," << t2y << "\t" << t3x << "," << t3y << std::endl;
#endif

            // create tanks at the coordinates // TODO make them not all commanders
            this->pieces.at(t1y).at(t1x) = std::make_unique<TankPiece>(this->players.at(i), protocol::TankModel::COMMANDER);
            this->pieces.at(t2y).at(t2x) = std::make_unique<TankPiece>(this->players.at(i), protocol::TankModel::COMMANDER);
            this->pieces.at(t3y).at(t3x) = std::make_unique<TankPiece>(this->players.at(i), protocol::TankModel::COMMANDER);
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
