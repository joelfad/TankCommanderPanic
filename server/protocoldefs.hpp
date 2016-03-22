/*
Project:  Tank Commander Panic
File:  protocoldefs.hpp
Author:  Leonardo Banderali
Description:  Definitions of simple types for the game protocol.
*/

#ifndef PROTOCOL_FIELD_TYPES_HPP
#define PROTOCOL_FIELD_TYPES_HPP

#include <cstdint>

namespace protocol {

using ServerMsgType = std::uint8_t;

using PieceID = std::uint32_t;
using PieceType = ServerMsgType;    // must be the same size
using TankCount = std::uint8_t;

using MapID = std::uint8_t;
using MapVersion = std::uint8_t;
using CoordinateX = std::uint8_t;
using CoordinateY = std::uint8_t;

using EventType = ServerMsgType;    // must be the same size

using PlayerID = std::uint16_t;

enum class Action: char {NONE, MOVE, SHOOT, QUIT};
enum class Direction: char {NONE, NORTH, EAST, SOUTH, WEST};

struct ActionMessage {
    PlayerID player;
    Action action;
    Direction direction;
    PieceID piece;
};

struct GameStateMessage {
    ServerMsgType message_type;
    MapID map_id;
    MapVersion map_version;
    PlayerID player_id;
    TankCount owned_tank_count;
    PieceID tank_piece_ids[];
};

struct CreatePieceMessage {
    union { ServerMsgType message_type; PieceType piece_type;};
    std::int32_t value;
    PieceID piece_id;
    CoordinateX piece_coord_x;
    CoordinateY piece_coord_y;
};

struct EventMessage {
    union { ServerMsgType message_type; EventType piece_type;};
    Direction direction;
    std::int32_t value;
    PieceID piece_id;
};

}

#endif // PROTOCOL_FIELD_TYPES_HPP
