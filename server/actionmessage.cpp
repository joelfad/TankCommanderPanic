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

    //auto player = msg.reinterprit_bits<ActionMessage::PieceID>();
}
