/*
Project:  Tank Commander Panic
File:  actionmessage.hpp
Author:  Leonardo Banderali
Description:  Simple type representing a message sent by a client.
*/

#ifndef ACTIONMESSAGE_HPP
#define ACTIONMESSAGE_HPP

#include "message.hpp"
#include "protocolfields.hpp"

namespace protocol {

class ActionMessageHandle {
    public:

        // constant and type members
        static constexpr auto size = sizeof(ActionMessage);

        // constructor
        ActionMessageHandle(const PlayerID& _player, const Action& action, const Direction& _direction, const PieceID& _piece);

        // getters
        auto player() const noexcept -> PlayerID;
        auto action() const noexcept -> Action;
        auto direction() const noexcept -> Direction;
        auto piece() const noexcept -> PieceID;

        // static functions
        static auto make_from_msg(const Message& msg) -> ActionMessageHandle;

    private:

        // private default constructor
        ActionMessageHandle();

        /*###############################################################################################
        ### To serialize and deserialize the fields in a message, a union of a struct and an array     ##
        ### of the same size is used. The struct defines the fields of the message in the order they   ##
        ### appear in the raw data. The array of bytes is the serialized representation of these       ##
        ### feilds. This approach is okay for the time being because messages are relatively small and ##
        ### simple. However, a proper serialization library may be a better solution later on.         ##
        ###############################################################################################*/

        // anonymous union used for serializing the fields of this message type
        union {
            ActionMessage msg_fields;
            unsigned char msg_data[sizeof(ActionMessage)];
        };
};

}

#endif // ACTIONMESSAGE_HPP
