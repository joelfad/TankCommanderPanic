/*
Project:  Tank Commander Panic
File:  actionmessage.cpp
Author:  Leonardo Banderali
Description:  Simple type representing a message sent by a client.
*/

#include "actionmessage.hpp"
#include "protocolerror.hpp"

#include <string>



//~constructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::ActionMessage::ActionMessage(const field_types::PlayerID& _player, const field_types::Action& action, const field_types::Direction& _direction, const field_types::field_types::PieceID& _piece)
    : player_id{_player}, act{_action}, dir{_direction}, piece_id{_piece} {}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessage::player() const noexcept -> field_types::PlayerID {
    return player_id;
}

auto protocol::ActionMessage::action() const noexcept -> field_types::Action {
    return act;
}

auto protocol::ActionMessage::direction() const noexcept -> field_types::Direction {
    return dir;
}

auto protocol::ActionMessage::piece() const noexcept -> field_types::PieceID {
    return piece_id;
}



//~non-member functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


/*
given a message `msg`, attempts to construct a corresponding `ActionMessage`, setting the fields appropriatly
@throws `protocol::MessageFormatError` if `msg` is not formated as an `ActionMessage`
@trhows `protocol::MessageLengthError` if `ms` is incorrect length for being an `ActionMessage`
*/
auto protocol::make_action_msg(const Message& msg) -> ActionMessage {
    if (msg.size() != ActionMessage::size)
        throw MessageLengthError{std::string{}, msg};

    /*
    field_types::PlayerID player = 0;
    player |= msg.byte(0) << 8;
    player |= msg.byte(1);
    field_types::Action action = msg.byte(2);
    field_types::Direction direction = msg.byte(3);
    field_types::PieceID piece = 0;
    piece |= msg.byte(4) << 8*3;
    piece |= msg.byte(5) << 8*2;
    piece |= msg.byte(6) << 8*1;
    piece |= msg.byte(7);
    */

    auto player = msg.reinterpret_bytes<field_types::PlayerID, 0>();
    auto action = msg.reinterpret_bytes<field_types::Action, 2>();
    auto direction = msg.reinterpret_bytes<field_types::Direction, 3>();
    auto piece = msg.reinterpret_bytes<field_types::PieceID, 4>();

    return ActionMessage{player, action, direction, piece};
}
