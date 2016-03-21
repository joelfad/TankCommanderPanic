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

class ActionMessage {
        // a struct defining the fields of this message type
        struct fields_t {
            field_types::PlayerID player;
            field_types::Action action;
            field_types::Direction direction;
            field_types::PieceID piece;
        };

    public:

        // constant and type members
        static constexpr auto size = sizeof(fields_t);

        // constructor
        ActionMessage(const field_types::PlayerID& _player, const field_types::Action& action, const field_types::Direction& _direction, const field_types::PieceID& _piece);

        // getters
        auto player() const noexcept -> field_types::PlayerID;
        auto action() const noexcept -> field_types::Action;
        auto direction() const noexcept -> field_types::Direction;
        auto piece() const noexcept -> field_types::PieceID;

        // static functions
        static auto make_from_msg(const Message& msg) -> ActionMessage;

    private:

        // private default constructor
        ActionMessage();

        /*###############################################################################################
        ### To serialize and deserialize the fields in a message, a union of a struct and an array     ##
        ### of the same size is used. The struct defines the fields of the message in the order they   ##
        ### appear in the raw data. The array of bytes is the serialized representation of these       ##
        ### feilds. This approach is okay for the time being because messages are relatively small and ##
        ### simple. However, a proper serialization library may be a better solution later on.         ##
        ###############################################################################################*/

        // anonymous union used for serializing the fields of this message type
        union {
            fields_t msg_fields;
            unsigned char msg_data[sizeof(fields_t)];
        };
};

}

#endif // ACTIONMESSAGE_HPP
