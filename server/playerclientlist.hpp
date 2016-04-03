/*
Project:  Tank Commander Panic
File:  playerclientlist.hpp
Author:  Leonardo Banderali
Description:  List of game clients.
*/

#ifndef PLAYERCLIENTLIST_HPP
#define PLAYERCLIENTLIST_HPP

#include "playerclient.hpp"
#include "protocol/protocoldefs.hpp"

#include <vector>

class PlayerClientList {
    public:
        using size_type = std::map<protocol::PlayerID, PlayerClient::Ptr>::size_type;
        using iterator = std::map<protocol::PlayerID, PlayerClient::Ptr>::iterator;
        using const_iterator = std::map<protocol::PlayerID, PlayerClient::Ptr>::const_iterator;

        auto size() const noexcept -> size_type;

        auto count() const noexcept -> int;

        void push_back(protocol::PlayerID player_id, const PlayerClient::Ptr& player);

        void erase(protocol::PlayerID player_id);

        void erase(const_iterator index);

        void send_all(const protocol::Message& msg) const;

        auto begin() -> iterator;

        auto end() -> iterator;

        auto cbegin() const -> const_iterator;

        auto cend() const -> const_iterator;

        auto operator[] (protocol::PlayerID&& player_id) -> PlayerClient::Ptr&;
        auto operator[] (const protocol::PlayerID& player_id) -> PlayerClient::Ptr&;

    private:
        std::map<protocol::PlayerID, PlayerClient::Ptr> players;
};

#endif // PLAYERCLIENTLIST_HPP
