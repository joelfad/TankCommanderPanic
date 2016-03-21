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

protocol::ActionMessage::ActionMessage(const field_types::PlayerID& _player, const field_types::Action& _action, const field_types::Direction& _direction, const field_types::PieceID& _piece)
    : msg_fields{_player, _action, _direction, _piece} {}



//~private constructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::ActionMessage::ActionMessage()
    : msg_fields{0, field_types::Action::MOVE, field_types::Direction::NONE, 0} {}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessage::player() const noexcept -> field_types::PlayerID {
    return msg_fields.player;
}

auto protocol::ActionMessage::action() const noexcept -> field_types::Action {
    return msg_fields.action;
}

auto protocol::ActionMessage::direction() const noexcept -> field_types::Direction {
    return msg_fields.direction;
}

auto protocol::ActionMessage::piece() const noexcept -> field_types::PieceID {
    return msg_fields.piece;
}



//~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessage::make_from_msg(const Message& msg) -> ActionMessage {
    if (msg.size() < ActionMessage::size)
        throw MessageLengthError("message is too short for `ActionMessage` type", msg);
    else if (msg.size() > ActionMessage::size)
        throw MessageLengthError("message is too long for `ActionMessage` type", msg);

    auto am = ActionMessage{};
    for (int i = 0; i < msg.size(); i++)
        am.msg_data[i] = msg.byte(i);
    return am;
}
