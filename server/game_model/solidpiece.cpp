/*
 * Project: Tank Commander Panic
 * File: solidpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract solid game piece model that can take damage.
 */

#include "solidpiece.hpp"

SolidPiece::SolidPiece() : GamePiece(false, false) {}

SolidPiece::SolidPiece(int max_health) :
        GamePiece(false, false), max_health(max_health) {

    // start with the maximum health
    this->health = this->max_health;
}

void SolidPiece::collide(TankPiece& tank) {
    GamePiece::collide(tank);
}

void SolidPiece::shot(int damage) {
    GamePiece::shot(damage);
    this->health -= damage;
}

void SolidPiece::set_max_health(int max_health)  {
    this->max_health = max_health;

    // continue with the maximum health
    this->health = this->max_health;
}
