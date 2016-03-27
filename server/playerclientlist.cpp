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

void PlayerClientList::push_back(const PlayerClient::Ptr& player) {
    players.push_back(player);
}

void PlayerClientList::erase(int index) {
    players.erase(players.cbegin() + index);
}

void PlayerClientList::erase(const_iterator position) {
    players.erase(position);
}

void PlayerClientList::send_all(const protocol::Message& msg) const {
    for (auto&& player : players)
        player->send(msg);
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

auto PlayerClientList::back() -> PlayerClient::Ptr& {
    return players.back();
}

auto PlayerClientList::back() const -> PlayerClient::Ptr const & {
    return players.back();
}

auto PlayerClientList::operator[] (int index) -> PlayerClient::Ptr& {
    return players[index];
}

auto PlayerClientList::operator[] (int index) const -> PlayerClient::Ptr const & {
    return players[index];
}
