/*
Project:  Tank Commander Panic
File:  gamestatemessage.hpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by the server to clients.
*/

#ifndef GAMESTATEMESSAGE_HPP
#define GAMESTATEMESSAGE_HPP

#include "protocoldefs.hpp"
#include "servermessagehandle.hpp"

#include <vector>

namespace protocol {

class GameStateMessageHandle : public ServerMessageHandle {
    public:
        GameStateMessageHandle();
        GameStateMessageHandle(ServerMsgType _message_type, MapID _map_id, MapVersion _map_version, PlayerID _player_id, const std::vector<PieceID>& _tank_ids);

        Message to_msg() const override;

        // setters
        void messsage_type(ServerMsgType msg_type) noexcept;
        void map_id(MapID id) noexcept;
        void map_version(MapVersion v) noexcept;
        void player_id(PlayerID id) noexcept;
        void tank_piece_ids(const std::vector<PieceID>& pids);
        void append_tank(PieceID pid);

        // getters
        auto messsage_type() const noexcept -> ServerMsgType;
        auto map_id() const noexcept -> MapID;
        auto map_version() const noexcept -> MapVersion;
        auto player_id() const noexcept -> PlayerID;
        auto tank_piece_ids() const noexcept -> std::vector<PieceID>;
        auto tank_id(int index) const noexcept -> PieceID;

    private:
        union {
            GameStateMessage msg_fields;
            unsigned char msg_data[sizeof(GameStateMessage)];
        };

        /*###########################################################################################
        ### Since the array in `GameStateMessage` that stores the tank IDs is forcibly made empty, ##
        ### the tank ID's have to be stored in a sparate vector. They also have to be manually     ##
        ### added to the message inside `to_msg()`.                                                ##
        ###########################################################################################*/
        std::vector<PieceID> tank_ids;
};

}

#endif // GAMESTATEMESSAGE_HPP
