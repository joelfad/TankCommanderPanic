/*
Project:  Tank Commander Panic
File:  protocolfieldtypes.hpp
Author:  Leonardo Banderali
Description:  Simple type for representing fields in protocol messages.
*/

#ifndef PROTOCOL_FIELD_TYPES_HPP
#define PROTOCOL_FIELD_TYPES_HPP

#include <cstdint>

namespace protocol { namespace field_types {

using PlayerID = std::uint16_t;
enum class Action: char {MOVE, SHOOT, QUIT};
enum class Direction: char {NONE, NORTH, EAST, SOUTH, WEST};
using PieceID = std::uint32_t;

}}

#endif // PROTOCOL_FIELD_TYPES_HPP
