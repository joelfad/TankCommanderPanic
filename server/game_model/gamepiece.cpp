/*
 * Project: Tank Commander Panic
 * File: gamepiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#include <cassert>

#include "gamepiece.hpp"

int GamePiece::count = 0;
/* set initial count to 0 */

GamePiece::GamePiece(bool clearshot, bool cleardrive) : clearshot(clearshot), cleardrive(cleardrive) {

    // assign id and increment counter, don't assign 0 as an id
    this->id = ++count;
}

void GamePiece::collide(TankPiece &tank) {

    // if this driven over, it had better be clear to drive on
    assert(this->isCleardrive());
}

void GamePiece::shot(int damage) {

    // if this was shot, it had better not be clear to shoot through
    assert(!this->isClearshot());
}
