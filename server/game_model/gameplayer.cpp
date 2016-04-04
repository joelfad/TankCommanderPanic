/*
 * Project: Tank Commander Panic
 * File: gameplayer.cpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#include "gameplayer.hpp"

protocol::PlayerID game_model::GamePlayer::next_id = 1;
/* set initial next_id to 1 */

game_model::GamePlayer::GamePlayer() {}

game_model::GamePlayer::GamePlayer(GamePlayer&& other) : name{std::move(other.name)}, id{other.id},
                                                         ammo{std::move(other.ammo)},
                                                         tank_count{std::move(other.tank_count)},
                                                         tank_ids{std::move(other.tank_ids)},
                                                         team_color{std::move(other.team_color)} {
    other.id = invalid_id;
}

game_model::GamePlayer& game_model::GamePlayer::operator=(GamePlayer&& rhs) {
    this->name = std::move(rhs.name);
    this->id = rhs.id;
    rhs.id = invalid_id;
    this->ammo = std::move(rhs.ammo);
    this->tank_count = std::move(rhs.tank_count);
    this->tank_ids = std::move(rhs.tank_ids);
    this->team_color = std::move(rhs.team_color);
    return *this;
}

game_model::GamePlayer game_model::GamePlayer::make_game_player() {
    auto result = game_model::GamePlayer();
    result.id = next_id++;
    result.ammo = 100;
    result.team_color = static_cast<protocol::TeamColor>(result.id - 1); // TODO make not ugly
    return result;
}
