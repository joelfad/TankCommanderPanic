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
#define DEBUG

game_model::GameModel::GameModel(std::string map_file_path) {
#ifdef DEBUG
    std::cout << "map file '" << map_file_path << "'...";
#endif

    // open the .map file
    std::ifstream map_file(map_file_path);
    if (map_file.is_open()) {
#ifdef DEBUG
        std::cout << "opened successfully" << std::endl;
#endif

        // collect basic info
        map_file >> this->map_name;     // map name
        map_file >> this->map_id;       // map id
        map_file >> this->map_version;  // map version
        map_file >> this->player_count; // player count
#ifdef DEBUG
        std::cout << "map name:     " << this->map_name << std::endl;
        std::cout << "map id:       " << this->map_id << std::endl;
        std::cout << "map version:  " << this->map_version << std::endl;
        std::cout << "player count: " << this->player_count << std::endl;
#endif

        // create game players
        this->players = std::vector<GamePlayer>(static_cast<unsigned long>(this->player_count));

        // collect player's starting positions
        for (int i = 0; i < this->player_count; i++) {

            // coordinates for the player's three tanks
            int t1x, t1y, t2x, t2y, t3x, t3y;

            // capture the line
            std::string line;
            std::getline(map_file, line);
#ifdef DEBUG
            std::cout << "tank coordinate line '" << line << "'" << std::endl;
#endif

            // collect the coordinates
            std::sscanf(line.c_str(), "%d,%d;%d,%d;%d,%d", &t1x, &t1y, &t2x, &t2y, &t3x, &t3y);
#ifdef DEBUG
            std::cout << "player " << i << " tank coordinates " << t1x << "," << t1y << "\t" << t2x << "," << t2y << "\t" << t3x << "," << t3y << std::endl;
#endif

            // create tanks at the coordinates // TODO make them not all commanders
            this->pieces[t1x][t1y] = TankPiece(this->players[i], protocol::TankModel::COMMANDER);
            this->pieces[t2x][t2y] = TankPiece(this->players[i], protocol::TankModel::COMMANDER);
            this->pieces[t3x][t3y] = TankPiece(this->players[i], protocol::TankModel::COMMANDER);
        }

        // collect map dimensions
        map_file >> this->map_width;    // map width
        map_file >> this->map_height;   // map height

        // collect tile properties and build map
        for (int i = 0; i < this->map_height; i++) {
            for (int j = 0; j < this->map_width; j++) {
                char tile;
                map_file >> tile;
                this->map[i][j] = Tile(tile);
            }
        }

        // close the file
        map_file.close();

    } else {

        // file is not opened
        // TODO fail appropriately
    }
}
