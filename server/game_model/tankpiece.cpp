/*
 * Project: Tank Commander Panic
 * File: tankpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#include "tankpiece.hpp"

TankPiece::TankPiece(GamePlayer& commander, TankModel model) :
        SolidPiece(model_max_health[static_cast<char>(model)]),
        power(model_power[static_cast<char>(model)]),
        range(model_range[static_cast<char>(model)]),
        speed(model_speed[static_cast<char>(model)]),
        commander(commander), model(model) {}
