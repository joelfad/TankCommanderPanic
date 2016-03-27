/*
 * Project: Tank Commander Panic
 * File: tankpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#include "tankpiece.hpp"

TankPiece::TankPiece(GamePlayer& commander) :
        SolidPiece(1), speed(1), power(1), range(1), commander(commander) {}
