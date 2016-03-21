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

protocol::ActionMessage::ActionMessage(const PlayerID& _player, const Action& action, const Direction& _direction, const PieceID& _piece)
    : player_id{_player}, act{_action}, dir{_direction}, piece_id{_piece} {}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessage::player() const noexcept -> PlayerID {
    return player_id;
}

auto protocol::ActionMessage::action() const noexcept -> Action {
    return act;
}

auto protocol::ActionMessage::direction() const noexcept -> Direction {
    return dir;
}

auto protocol::ActionMessage::piece() const noexcept -> PieceID {
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
    ActionMessage::PlayerID player = 0;
    player |= msg.byte(0) << 8;
    player |= msg.byte(1);
    ActionMessage::Action action = msg.byte(2);
    ActionMessage::Direction direction = msg.byte(3);
    ActionMessage::PieceID piece = 0;
    piece |= msg.byte(4) << 8*3;
    piece |= msg.byte(5) << 8*2;
    piece |= msg.byte(6) << 8*1;
    piece |= msg.byte(7);
    */

    auto player = msg.reinterpret_bytes<ActionMessage::PlayerID, 0>();
    auto action = msg.reinterpret_bytes<ActionMessage::Action, 2>();
    auto direction = msg.reinterpret_bytes<ActionMessage::Direction, 3>();
    auto piece = msg.reinterpret_bytes<ActionMessage::PieceID, 4>();

    return ActionMessage{player, action, direction, piece};
}
