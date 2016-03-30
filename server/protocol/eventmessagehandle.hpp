/*
Project:  Tank Commander Panic
File:  eventmessagehandle.hpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by clients.
*/

#ifndef EVENTMESSAGEHANDLE_HPP
#define EVENTMESSAGEHANDLE_HPP

#include "servermessagehandle.hpp"
#include "protocoldefs.hpp"

namespace protocol {

class EventMessageHandle : public ServerMessageHandle {
    public:
        EventMessageHandle(ServerMsgType msg_type, Direction dir, std::int32_t val, PieceID pid);
        //EventMessageHandle(EventType evt_type, Direction dir, std::int32_t val, PieceID pid);
        /* cannot overload because `EventType` and `ServerMsgType` are the same type */
        EventMessageHandle();

        Message to_msg() const override;

        // setters
        void message_type(ServerMsgType msg_type) noexcept;
        void event_type(EventType evt_type) noexcept;
        void direction(Direction dir) noexcept;
        void value(std::int32_t val) noexcept;
        void piece_id(PieceID pid) noexcept;

        // getters
        auto message_type() const noexcept -> ServerMsgType;
        auto event_type() const noexcept -> EventType;
        auto direction() const noexcept -> Direction;
        auto value() const noexcept -> std::int32_t;
        auto piece_id() const noexcept -> PieceID;

    private:
        union{
            EventMessage msg_fields;
            unsigned char msg_data[sizeof(EventMessage)];
        };
};

}

#endif // EVENTMESSAGEHANDLE_HPP
