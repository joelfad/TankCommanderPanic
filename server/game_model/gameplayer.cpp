/*
 * Project: Tank Commander Panic
 * File: gameplayer.cpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#include "gameplayer.hpp"

protocol::PlayerID game_model::GamePlayer::next_id = 1;
/* set initial next_id to 1 */

game_model::GamePlayer::GamePlayer() {

    // assign id and next_id
    this->id = next_id++;

    // starting ammo count
    this->ammo = INT32_MAX;
}

