/*
 * Project: Tank Commander Panic
 * File: gameplayer.cpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#include "gameplayer.hpp"

int GamePlayer::count = 0;
/* set initial count to 0 */

GamePlayer::GamePlayer(std::string name): name(name) {

    // assign id and increment counter, don't assign 0 as an id
    this->id = ++count;
}

