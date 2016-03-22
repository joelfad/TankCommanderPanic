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

protocol::ActionMessageHandle::ActionMessageHandle(const PlayerID& _player, const Action& _action, const Direction& _direction, const PieceID& _piece)
    : msg_fields{_player, _action, _direction, _piece} {}



//~private constructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::ActionMessageHandle::ActionMessageHandle()
    : msg_fields{0, Action::MOVE, Direction::NONE, 0} {}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessageHandle::player() const noexcept -> PlayerID {
    return msg_fields.player;
}

auto protocol::ActionMessageHandle::action() const noexcept -> Action {
    return msg_fields.action;
}

auto protocol::ActionMessageHandle::direction() const noexcept -> Direction {
    return msg_fields.direction;
}

auto protocol::ActionMessageHandle::piece() const noexcept -> PieceID {
    return msg_fields.piece;
}



//~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::ActionMessageHandle::make_from_msg(const Message& msg) -> ActionMessageHandle {
    if (msg.size() < ActionMessageHandle::size)
        throw MessageLengthError("message is too short for `ActionMessage` type", msg);
    else if (msg.size() > ActionMessageHandle::size)
        throw MessageLengthError("message is too long for `ActionMessage` type", msg);

    auto am = ActionMessageHandle{};
    for (int i = 0; i < msg.size(); i++)
        am.msg_data[i] = msg.byte(i);
    return am;
}
