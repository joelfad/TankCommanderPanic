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

constexpr unsigned short port = 4410;

using ServerMsgType = std::uint8_t;

static constexpr ServerMsgType GameStateMessageValue = 1;

enum class PieceType: ServerMsgType {
    // 2 - 7 brick types
    HEALTH=8, AMMO=9, DECORATION=10,
    // 11 - 15 unreserved
    RED_COMMANDER       = 16, RED_INTERCEPTOR       = 17, RED_ELIMINATOR    = 18, RED_NEGOTIATOR    = 19,
    BLUE_COMMANDER      = 20, BLUE_INTERCEPTOR      = 21, BLUE_ELIMINATOR   = 22, BLUE_NEGOTIATOR   = 23,
    YELLOW_COMMANDER    = 24, YELLOW_INTERCEPTOR    = 25, YELLOW_ELIMINATOR = 26, YELLOW_NEGOTIATOR = 27,
    GREEN_COMMANDER     = 28, GREEN_INTERCEPTOR     = 29, GREEN_ELIMINATOR  = 30, GREEN_NEGOTIATOR  = 31
};

enum class TeamColor: ServerMsgType {RED=0, BLUE=4, YELLOW=8, GREEN=12};
enum class TankModel: ServerMsgType {COMMANDER=0, INTERCEPTOR=1, ELIMINATOR=2, NEGOTIATOR=3};

PieceType tank_type(TeamColor color, TankModel model);
/* calculate the PieceType from the TeamColor and TankModel (defined in tankpiece.cpp) */

TankModel tank_model(PieceType);
/* calculate the Model from the PieceType */

enum class EventType: ServerMsgType {
    UPDATE_AMMO = 32, UPDATE_HEALTH = 33, DESTROY_GAME_PIECE = 34, MOVE_GAME_PIECE = 35, GAME_START=36, GAME_OVER = 37
};

enum EndGameState: std::int32_t {LOSE, WIN};

using PieceID = std::uint32_t;
using TankCount = std::uint8_t;

using MapID = std::uint8_t;
using MapVersion = std::uint8_t;
using CoordinateX = std::uint8_t;
using CoordinateY = std::uint8_t;

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
### is left present for the sake of agreeing with the protocol documentation.  ##
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
