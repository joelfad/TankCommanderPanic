/*
 * Project: Tank Commander Panic
 * File: gamepiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#include "gamepiece.hpp"

int GamePiece::count = 0;
/* set initial count to 0 */

GamePiece::GamePiece() {

    // assign id and increment counter, don't assign 0 as an id
    this->id = ++count;
}

