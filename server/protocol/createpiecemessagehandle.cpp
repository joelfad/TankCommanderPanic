/*
Project:  Tank Commander Panic
File:  createpiecemessagehandle.cpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by clients.
*/

#include "createpiecemessagehandle.hpp"



//~constructors~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::CreatePieceMessageHandle::CreatePieceMessageHandle(ServerMsgType _message_type, std::int32_t _value, PieceID _piece_id, CoordinateX _piece_coord_x, CoordinateY _piece_coord_y)
    : msg_fields{_message_type, _value, _piece_id, _piece_coord_x, _piece_coord_y} {}

/*protocol::CreatePieceMessageHandle::CreatePieceMessageHandle(PieceType _piece_type, std::int32_t _value, PieceID _piece_id, CoordinateX _piece_coord_x, CoordinateY _piece_coord_y)
    : msg_fields{_piece_type, _value, _piece_id, _piece_coord_x, _piece_coord_y} {}*/
/* cannot overload because `PieceType` and `ServerMsgType` are the same type */

protocol::CreatePieceMessageHandle::CreatePieceMessageHandle()
    : msg_fields{0,0,0,0,0} {}



//~overriden functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::Message protocol::CreatePieceMessageHandle::to_msg() const {
    return Message{msg_data, sizeof(msg_data)};
}



//~setters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void protocol::CreatePieceMessageHandle::message_type(ServerMsgType msg_type) noexcept {
    msg_fields.message_type = msg_type;
}

void protocol::CreatePieceMessageHandle::piece_type(PieceType ptype) noexcept {
    msg_fields.piece_type = ptype;
}

void protocol::CreatePieceMessageHandle::value(std::int32_t val) noexcept {
    msg_fields.value = val;
}

void protocol::CreatePieceMessageHandle::piece_id(PieceID pid) noexcept {
    msg_fields.piece_id = pid;
}

void protocol::CreatePieceMessageHandle::piece_coord_x(CoordinateX x) noexcept {
    msg_fields.piece_coord_x = x;
}

void protocol::CreatePieceMessageHandle::piece_coord_y(CoordinateY y) noexcept {
    msg_fields.piece_coord_y = y;
}



// getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::CreatePieceMessageHandle::message_type() const noexcept -> ServerMsgType {
    return msg_fields.message_type;
}

auto protocol::CreatePieceMessageHandle::piece_type() const noexcept -> PieceType {
    return msg_fields.piece_type;
}

auto protocol::CreatePieceMessageHandle::value() const noexcept -> std::int32_t {
    return msg_fields.value;
}

auto protocol::CreatePieceMessageHandle::piece_id() const noexcept -> PieceID {
    return msg_fields.piece_id;
}

auto protocol::CreatePieceMessageHandle::piece_coord_x() const noexcept -> CoordinateX {
    return msg_fields.piece_coord_x;
}

auto protocol::CreatePieceMessageHandle::piece_coord_y() const noexcept -> CoordinateY {
    return msg_fields.piece_coord_y;
}
