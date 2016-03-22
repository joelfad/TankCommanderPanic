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

using PlayerID = std::uint16_t;
enum class Action: char {NONE, MOVE, SHOOT, QUIT};
enum class Direction: char {NONE, NORTH, EAST, SOUTH, WEST};
using PieceID = std::uint32_t;

struct ActionMessage {
    PlayerID player;
    Action action;
    Direction direction;
    PieceID piece;
};

}

#endif // PROTOCOL_FIELD_TYPES_HPP
