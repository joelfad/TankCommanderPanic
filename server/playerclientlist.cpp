/*
Project:  Tank Commander Panic
File:  playerclientlist.cpp
Author:  Leonardo Banderali
Description:  List of game clients.
*/

#include "playerclientlist.hpp"



//~public functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto PlayerClientList::size() const noexcept -> size_type {
    return players.size();
}

auto PlayerClientList::count() const noexcept -> int {
    return players.size();
}

void PlayerClientList::push_back(protocol::PlayerID player_id, const PlayerClient::Ptr& player) {
    players.insert(std::make_pair(player_id, player));
}

void PlayerClientList::erase(protocol::PlayerID player_id) {
    players.erase(player_id);
}

void PlayerClientList::erase(const_iterator index) {
    players.erase(index);
}

void PlayerClientList::send_all(const protocol::Message& msg) const {
    for (auto&& player : players)
        player.second->send(msg);
}

auto PlayerClientList::begin() -> iterator {
    return players.begin();
}

auto PlayerClientList::end() -> iterator {
    return players.end();
}

auto PlayerClientList::cbegin() const -> const_iterator {
    return players.cbegin();
}

auto PlayerClientList::cend() const -> const_iterator {
    return players.cend();
}

auto PlayerClientList::operator[] (protocol::PlayerID&& player_id) -> PlayerClient::Ptr& {
    return players[player_id];
}

auto PlayerClientList::operator[] (const protocol::PlayerID& player_id) -> PlayerClient::Ptr& {
    return players[player_id];
}
