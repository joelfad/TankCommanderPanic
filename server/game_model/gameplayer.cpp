/*
 * Project: Tank Commander Panic
 * File: gameplayer.cpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#include "gameplayer.hpp"

protocol::PlayerID GamePlayer::next_id = 1;
/* set initial next_id to 1 */

GamePlayer::GamePlayer(std::string name): name(name) {

    // assign id and next_id
    this->id = next_id++;
}

