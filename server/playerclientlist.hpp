/*
Project:  Tank Commander Panic
File:  playerclientlist.hpp
Author:  Leonardo Banderali
Description:  List of game clients.
*/

#ifndef PLAYERCLIENTLIST_HPP
#define PLAYERCLIENTLIST_HPP

#include "playerclient.hpp"

#include <vector>

class PlayerClientList {
    public:
        using size_type = std::vector<PlayerClient::Ptr>::size_type;
        using iterator = std::vector<PlayerClient::Ptr>::iterator;
        using const_iterator = std::vector<PlayerClient::Ptr>::const_iterator;

        auto size() const noexcept -> size_type;

        auto count() const noexcept -> int;

        void push_back(const PlayerClient::Ptr& player);

        void erase(int index);

        void erase(const_iterator position);

        void send_all(const protocol::Message& msg) const;

        auto begin() -> iterator;

        auto end() -> iterator;

        auto cbegin() const -> const_iterator;

        auto cend() const -> const_iterator;

        auto back() -> PlayerClient::Ptr&;

        auto back() const -> PlayerClient::Ptr const &;

        auto operator[] (int index) -> PlayerClient::Ptr&;
        auto operator[] (int index) const -> PlayerClient::Ptr const &;

    private:
        std::vector<PlayerClient::Ptr> players;
};

#endif // PLAYERCLIENTLIST_HPP
