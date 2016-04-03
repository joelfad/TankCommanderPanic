/*
 * Project: Tank Commander Panic
 * File: gamemodel.hpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

#ifndef SERVER_GAMEMODEL_HPP
#define SERVER_GAMEMODEL_HPP

#include <vector>
#include <memory>

#include "tile.hpp"
#include "gamepiece.hpp"
#include "gameplayer.hpp"
#include "../protocol/protocoldefs.hpp"

namespace game_model {

class GameModel {
public:

    GameModel(std::string map_file_path);

    auto get_player_count() const noexcept { return player_count; }

    template<class T>
    using map_vector = std::vector<std::vector<std::unique_ptr<T>>>;

    void attempt_to_move(protocol::PieceID piece_id, protocol::Direction direction);
    void attempt_to_shoot(protocol::PieceID piece_id, protocol::Direction direction);
    /* handle game actions */

private:

    int player_count;
    int map_width;
    int map_height;

    std::string map_name;
    protocol::MapID map_id;
    protocol::MapVersion map_version;

    map_vector<Tile> map;
    /* 2D vector of tiles composes the map of the battlefield */

    map_vector<GamePiece> pieces;
    /* 2D vector of game pieces on the battlefield */

    std::vector<GamePlayer> players;
    /* collection of players */

    void game_piece_coordinates(protocol::PieceID id, protocol::CoordinateX& x, protocol::CoordinateY& y);
    /* find the coordinates of a game piece based on its id */

};

}
#endif // SERVER_GAMEMODEL_HPP
