/*
 * Project: Tank Commander Panic
 * File: tankpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#include "tankpiece.hpp"

TankPiece::TankPiece(GamePlayer& commander, TankModel model) : commander(commander), model(model) {
    set_max_health(TankPiece::model_max_health[static_cast<char>(model)]);
}

constexpr int TankPiece::model_max_health[];
