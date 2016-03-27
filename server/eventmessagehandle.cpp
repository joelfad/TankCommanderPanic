/*
Project:  Tank Commander Panic
File:  eventmessagehandle.cpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by clients.
*/

#include "eventmessagehandle.hpp"

//~constructors~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::EventMessageHandle::EventMessageHandle(ServerMsgType msg_type, Direction dir, std::int32_t val, PieceID pid)
    : msg_fields{msg_type, dir, val, pid} {}

protocol::EventMessageHandle::EventMessageHandle(EventType evt_type, Direction dir, std::int32_t val, PieceID pid)
    : msg_fields{evt_type, dir, val, pid} {}

protocol::EventMessageHandle::EventMessageHandle()
    : msg_fields{0, 0, 0, 0} {}



//~overriden functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::Message protocol::EventMessageHandle::to_msg() const override {
    return Message{msg_data, sizeof(msg_data)};
}



//~setters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void protocol::EventMessageHandle::message_type(ServerMsgType msg_type) noexcept {
    msg_fields.message_type = msg_type;
}

void protocol::EventMessageHandle::event_type(EventType evt_type) noexcept {
    msg_fields.event_type = evt_type;
}

void protocol::EventMessageHandle::direction(Direction dir) noexcept {
    msg_fields.direction = dir;
}

void protocol::EventMessageHandle::value(std::int32_t val) noexcept {
    msg_fields.value = val;
}

void protocol::EventMessageHandle::piece_id(PieceID pid) noexcept {
    msg_fields.piece_id = pid;
}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::EventMessageHandle::message_type() const noexcept -> ServerMsgType {
    return msg_fields.message_type;
}

auto protocol::EventMessageHandle::event_type() const noexcept -> EventType {
    return msg_fields.event_type;
}

auto protocol::EventMessageHandle::direction() const noexcept -> Direction {
    return msg_fields.direction;
}

auto protocol::EventMessageHandle::value() const noexcept -> std::int32_t {
    return msg_fields.value;
}

auto protocol::EventMessageHandle::piece_id() const noexcept -> PieceID {
    return msg_fields.piece_id;
}
