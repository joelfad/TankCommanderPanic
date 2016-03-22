/*
 * Project: Tank Commander Panic
 * File: gameplayer.cpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#include "gameplayer.hpp"

GamePlayer::GamePlayer(std::string name) {

    // assign id and increment counter
    this->id = count++;
}

