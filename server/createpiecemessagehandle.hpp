/*
Project:  Tank Commander Panic
File:  createpiecemessagehandle.hpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by clients.
*/

#ifndef CREATEPIECEMESSAGEHANDLE_HPP
#define CREATEPIECEMESSAGEHANDLE_HPP

#include "servermessagehandle.hpp"
#include "protocoldefs.hpp"

namespace protocol {

class CreatePieceMessageHandle : public ServerMessageHandle {
    public:
        CreatePieceMessageHandle(ServerMsgType _message_type, std::int32_t _value, PieceID _piece_id, CoordinateX _piece_coord_x, CoordinateY _piece_coord_y);
        CreatePieceMessageHandle(PieceType _piece_type, std::int32_t _value, PieceID _piece_id, CoordinateX _piece_coord_x, CoordinateY _piece_coord_y);
        CreatePieceMessageHandle();

        Message to_msg() const override;

        // setters
        void message_type(ServerMsgType msg_type) noexcept;
        void piece_type(PieceType ptype) noexcept;
        void value(std::int32_t val) noexcept;
        void piece_id(PieceID pid) noexcept;
        void piece_coord_x(CoordinateX x) noexcept;
        void piece_coord_y(CoordinateY y) noexcept;

        // getters
        auto message_type() const noexcept -> ServerMsgType;
        auto piece_type() const noexcept -> PieceType;
        auto value() const noexcept -> std::int32_t;
        auto piece_id() const noexcept -> PieceID;
        auto piece_coord_x() const noexcept -> CoordinateX;
        auto piece_coord_y() const noexcept -> CoordinateY;

    private:
        union {
            CreatePieceMessage msg_fields;
            unsigned char msg_data[sizeof(CreatePieceMessage)];
        };
};

}

#endif // CREATEPIECEMESSAGEHANDLE_HPP
