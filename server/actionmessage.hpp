/*
Project:  Tank Commander Panic
File:  actionmessage.hpp
Author:  Leonardo Banderali
Description:  Simple type representing a message sent by a client.
*/

#ifndef ACTIONMESSAGE_HPP
#define ACTIONMESSAGE_HPP

#include "message.hpp"

#include <cstdint>

namespace protocol {

class ActionMessage {
    public:

        // member types
        using PlayerID = std::uint16_t;
        enum class Action: char {MOVE, SHOOT, QUIT};
        enum class Direction: char {NORTH, SOUTH, EAST, WEST, NONE};
        using PieceID = std::uint32_t;
        static constexpr auto size = sizeof(PlayerID) + sizeof(Action) + sizeof(Direction) + sizeof(PieceID);

        // constructor
        ActionMessage(const PlayerID& _player, const Action& action, const Direction& _direction, const PieceID& _piece);

        // getters
        auto player() const noexcept -> PlayerID;
        auto action() const noexcept -> Action;
        auto direction() const noexcept -> Direction;
        auto piece() const noexcept -> PieceID;

    private:
        PlayerID player_id;
        Action act;
        Direction dir;
        PieceID piece_id;
};

auto make_action_msg(const Message& msg) -> ActionMessage;
/*  given a message `msg`, attempts to construct a corresponding `ActionMessage`, setting the fields appropriatly
    @throws `protocol::MessageFormatError` if `msg` is not formated as an `ActionMessage`
    @trhows `protocol::MessageLengthError` if `ms` is incorrect length for being an `ActionMessage`
*/

}

#endif // ACTIONMESSAGE_HPP
