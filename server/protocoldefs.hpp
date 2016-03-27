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

//~message structures~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*#########################################################################################
### The following structures are a representation of how fields are ordered and sized in ##
### for different message formats/types. They do not provide any form of abstraction and ##
### should therefore only be accessed inderectly. Using resource handles for these is    ##
### highly recommended.                                                                  ##
###                                                                                      ##
### In the future, these message formats may be encapsulated into more complex classes   ##
### in order to provide better abstraction.                                              ##
#########################################################################################*/

struct ActionMessage {
    PlayerID player;
    Action action;
    Direction direction;
    PieceID piece;
};

/*###############################################################################
### For the `GameStateMessage`, it is impossible to predict how many tanks     ##
### the player being messaged will own. It is also not possible to dynamically ##
### resize arrays. So, `tank_piece_ids[]` is forcibly made empty. The field    ##
### is left preset for the sake of agreeing with the protocol documentation.   ##
### It is therefore crucial that instances of this structure never be accessed ##
### directly.                                                                  ##
###############################################################################*/
struct GameStateMessage {
    ServerMsgType message_type;
    MapID map_id;
    MapVersion map_version;
    PlayerID player_id;
    TankCount owned_tank_count;
    PieceID tank_piece_ids[] = {};  // force array to be empty
};

struct CreatePieceMessage {
    union { ServerMsgType message_type; PieceType piece_type;};
    std::int32_t value;
    PieceID piece_id;
    CoordinateX piece_coord_x;
    CoordinateY piece_coord_y;
};

struct EventMessage {
    union { ServerMsgType message_type; EventType event_type;};
    Direction direction;
    std::int32_t value;
    PieceID piece_id;
};

}

#endif // PROTOCOL_FIELD_TYPES_HPP
