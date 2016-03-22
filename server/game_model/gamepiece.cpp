/*
 * Project: Tank Commander Panic
 * File: gamepiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#include "gamepiece.hpp"

GamePiece::GamePiece() {

    // assign id and increment counter
    this->id = count++;
}

