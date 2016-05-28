/*
Project:  Tank Commander Panic
File:  actionmessagehandle.cpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by clients.
*/

#include "actionmessagehandle.hpp"
#include "protocolerror.hpp"
#include "serialize.hpp"

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
    auto am = ActionMessageHandle{};
    serial::deserialize_into(msg.data(), am.msg_fields.player, am.msg_fields.action, am.msg_fields.direction, am.msg_fields.piece);
    return am;
}
