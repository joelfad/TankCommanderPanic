/*
 * Project: Tank Commander Panic
 * File: solidpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract solid game piece model that can take damage.
 */

#include "solidpiece.hpp"

game_model::SolidPiece::SolidPiece() : GamePiece(false, false) {}

game_model::SolidPiece::SolidPiece(int max_health) : GamePiece(false, false), max_health(max_health) {

    // start with the maximum health
    this->health = this->max_health;
}

void game_model::SolidPiece::collide(TankPiece& tank) {
    GamePiece::collide(tank);
}

void game_model::SolidPiece::shot(int damage) {
    GamePiece::shot(damage);
    this->health -= damage;
}

void game_model::SolidPiece::set_max_health(int max_health)  {
    this->max_health = max_health;

    // continue with the maximum health
    this->health = this->max_health;
}
