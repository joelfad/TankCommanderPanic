/*
 * Project: Tank Commander Panic
 * File: tankpiece.hpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#ifndef SERVER_TANKPIECE_HPP
#define SERVER_TANKPIECE_HPP

#include "solidpiece.hpp"

class GamePlayer;

enum class TankModel: char {COMMANDER, INTERCEPTOR, ELIMINATOR, NEGOTIATOR};

class TankPiece : public SolidPiece {
public:

    TankPiece(GamePlayer& commander, TankModel model);

    int getPower() const noexcept { return model_power[static_cast<char>(model)]; }

    int getRange() const noexcept { return model_range[static_cast<char>(model)]; }

    int getSpeed() const noexcept { return model_speed[static_cast<char>(model)]; }

private:
    static constexpr int model_max_health[] = { 50,  30, 100,  20}; // hit points
    static constexpr int model_power[]      = { 30,  30,  80,  50}; // hit points
    static constexpr int model_range[]      = {  6,   6,   3,  12}; // tiles
    static constexpr int model_speed[]      = {  2,   4,   1,   1}; // tiles per second

    TankModel model;
    /* the model of the tank determines its gameplay characteristics */

    GamePlayer& commander;
    /* the GamePlayer that commands this tank */

};


#endif //SERVER_TANKPIECE_HPP
