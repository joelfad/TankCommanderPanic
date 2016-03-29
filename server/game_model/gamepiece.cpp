/*
 * Project: Tank Commander Panic
 * File: gamepiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#include <cassert>

#include "gamepiece.hpp"

protocol::PieceID GamePiece::next_id = 1;
/* set initial next_id to 1 */

GamePiece::GamePiece(bool clearshot, bool cleardrive) : clear_shot(clearshot), clear_drive(cleardrive) {

    // assign id and increment next_id
    this->id = next_id++;
}

void GamePiece::collide(TankPiece &tank) {

    // if this driven over, it had better be clear to drive on
    assert(this->is_clear_drive());  // TODO replace with exception ModelEventError
}

void GamePiece::shot(int damage) {

    // if this was shot, it had better not be clear to shoot through
    assert(!this->is_clear_shot());  // TODO replace with exception ModelEventError
}
