/*
 * Project: Tank Commander Panic
 * File: solidpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract solid game piece model that can take damage.
 */

#include "solidpiece.hpp"

SolidPiece::SolidPiece() : clearshot(false), cleardrive(false) {
    // TODO define starting health
}

void SolidPiece::shot(int damage) {
    this->health -= damage;
}



