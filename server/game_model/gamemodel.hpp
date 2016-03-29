/*
 * Project: Tank Commander Panic
 * File: gamemodel.hpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

#ifndef SERVER_GAMEMODEL_HPP
#define SERVER_GAMEMODEL_HPP

#include <vector>

#include "tile.hpp"
#include "gamepiece.hpp"
#include "gameplayer.hpp"
#include "../protocoldefs.hpp"

class GameModel {
public:

    GameModel(protocol::MapID map_id, protocol::MapVersion map_version);

private:

    std::vector<std::vector<Tile>> map;
    /* 2D vector of tiles composes the map of the battlefield */

    std::vector<std::vector<GamePiece>> pieces;
    /* 2D vector of game pieces on the battlefield */

    std::vector<GamePlayer> players;
    /* collection of players */

};

#endif // SERVER_GAMEMODEL_HPP
