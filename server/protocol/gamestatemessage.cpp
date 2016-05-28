/*
Project:  Tank Commander Panic
File:  gamestatemessage.cpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by the server to clients.
*/

#include "gamestatemessage.hpp"



//~constructors~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::GameStateMessageHandle::GameStateMessageHandle() : GameStateMessageHandle{0, 0, 0, std::vector<PieceID>{}} {}

protocol::GameStateMessageHandle::GameStateMessageHandle(MapID _map_id, MapVersion _map_version, PlayerID _player_id, const std::vector<PieceID>& _tank_ids) {
    msg_fields.message_type = protocol::GameStateMessageValue;
    msg_fields.map_id = _map_id;
    msg_fields.map_version = _map_version;
    msg_fields.player_id = _player_id;
    msg_fields.owned_tank_count = static_cast<TankCount>(tank_ids.size());
    tank_ids = _tank_ids;
}



//~overriden functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protocol::Message protocol::GameStateMessageHandle::to_msg() const {
    /*###########################################################################################
    ### Since the array in `GameStateMessage` that stores the tank IDs is forcibly made empty, ##
    ### the tank ID's have to be inserted into the message manually.                           ##
    ###########################################################################################*/

    // put message bytes into returned message
    /*for (auto&& b : msg_data)
        msg.push_back(b);*/
    auto buff = serial::serialize(msg_fields.message_type,
                                  msg_fields.map_id,
                                  msg_fields.map_version,
                                  msg_fields.player_id,
                                  msg_fields.owned_tank_count
                                  );

    auto msg = Message::byte_vector{};   // temporarily stores the message data

    // reserve enough bytes for the message and
    msg.reserve(buff.size() + tank_ids.size());

    // put already serialized values in the message
    for (auto&& b : buff) {
        msg.push_back(b);
    }

    // put tank IDs into returned message
    for (auto&& id : tank_ids) {
        auto serialized_tank = serial::serialize(id);
        for (auto&& b : serialized_tank) {
            msg.push_back(b);
        }
    }

    return Message(msg);
}



//~setters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void protocol::GameStateMessageHandle::map_id(MapID id) noexcept {
    msg_fields.map_id = id;
}

void protocol::GameStateMessageHandle::map_version(MapVersion v) noexcept {
    msg_fields.map_version = v;
}

void protocol::GameStateMessageHandle::player_id(PlayerID id) noexcept {
    msg_fields.player_id = id;
}

void protocol::GameStateMessageHandle::tank_piece_ids(const std::vector<PieceID>& pids) {
    tank_ids = pids;
    msg_fields.owned_tank_count = static_cast<TankCount>(tank_ids.size());
}

void protocol::GameStateMessageHandle::append_tank(PieceID pid) {
    tank_ids.push_back(pid);
    msg_fields.owned_tank_count = static_cast<TankCount>(tank_ids.size());
}



//~getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto protocol::GameStateMessageHandle::map_id() const noexcept -> MapID {
    return msg_fields.map_id;
}

auto protocol::GameStateMessageHandle::map_version() const noexcept -> MapVersion {
    return msg_fields.map_version;
}

auto protocol::GameStateMessageHandle::player_id() const noexcept -> PlayerID {
    return msg_fields.player_id;
}

auto protocol::GameStateMessageHandle::tank_piece_ids() const noexcept -> std::vector<PieceID> {
    return tank_ids;
}

auto protocol::GameStateMessageHandle::tank_id(int index) const noexcept -> PieceID {
    return tank_ids[index];
}
