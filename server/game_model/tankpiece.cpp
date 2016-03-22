/*
 * Project: Tank Commander Panic
 * File: tankpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#include "tankpiece.hpp"

TankPiece::TankPiece(GamePlayer commander) : health(5), speed(1), power(1), range(5), commander(commander) {}

