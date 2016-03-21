/*
Project:  Tank Commander Panic
File:  actionmessage.hpp
Author:  Leonardo Banderali
Description:  Simple type representing a message sent by a client.
*/

#ifndef ACTIONMESSAGE_HPP
#define ACTIONMESSAGE_HPP

#include "message.hpp"
#include "protocolfields.hpp"

namespace protocol {

class ActionMessage {
    public:

        // member types and constants
        static constexpr auto size = sizeof(field_types::PlayerID) + sizeof(field_types::Action) + sizeof(field_types::Direction) + sizeof(PieceID);

        // constructor
        ActionMessage(const field_types::PlayerID& _player, const field_types::Action& action, const field_types::Direction& _direction, const PieceID& _piece);

        // getters
        auto player() const noexcept -> field_types::PlayerID;
        auto action() const noexcept -> field_types::Action;
        auto direction() const noexcept -> field_types::Direction;
        auto piece() const noexcept -> PieceID;

    private:
        field_types::PlayerID player_id;
        field_types::Action act;
        field_types::Direction dir;
        PieceID piece_id;
};

auto make_action_msg(const Message& msg) -> ActionMessage;
/*  given a message `msg`, attempts to construct a corresponding `ActionMessage`, setting the fields appropriatly
    @throws `protocol::MessageFormatError` if `msg` is not formated as an `ActionMessage`
    @trhows `protocol::MessageLengthError` if `ms` is incorrect length for being an `ActionMessage`
*/

}

#endif // ACTIONMESSAGE_HPP
