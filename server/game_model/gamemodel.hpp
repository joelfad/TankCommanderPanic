/*
 * Project: Tank Commander Panic
 * File: gamemodel.hpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

#ifndef SERVER_GAMEMODEL_HPP
#define SERVER_GAMEMODEL_HPP

#include <vector>
#include <map>
#include <memory>

#include "tile.hpp"
#include "gamepiece.hpp"
#include "gameplayer.hpp"
#include "../protocol/protocoldefs.hpp"
#include "../protocol/message.hpp"
#include "../messageenvelope.hpp"

namespace game_model {

class GameModel {
public:

    GameModel(std::string map_file_path);

    auto get_player_count() const noexcept { return player_count; }

    template<class T>
    using map_vector = std::vector<std::vector<std::unique_ptr<T>>>;

    std::vector<MessageEnvelope> attempt_to_move(protocol::PieceID piece_id, protocol::Direction direction);
    std::vector<MessageEnvelope> attempt_to_shoot(protocol::PieceID piece_id, protocol::Direction direction,
                                                  protocol::PlayerID player_id);
    /* handle game actions */

    auto get_players() const noexcept -> const std::map<protocol::PlayerID, GamePlayer>& { return this->players; }
    auto get_map_version() const noexcept -> protocol::MapVersion { return map_version; }
    auto get_map_id() const noexcept -> protocol::MapID { return map_id; }

    std::vector<protocol::PieceID> tanks_owned_by(protocol::PlayerID player_id);

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

    std::map<protocol::PlayerID, GamePlayer> players;
    /* collection of players */

    void game_piece_coordinates(protocol::PieceID id, protocol::CoordinateX& x, protocol::CoordinateY& y);
    /* find the coordinates of a game piece based on its id */

};

}
#endif // SERVER_GAMEMODEL_HPP
