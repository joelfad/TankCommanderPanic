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

    TankPiece(GamePlayer& commander);
    /* Tank with default properties */

    // TankPiece(GamePlayer& commander, TankModel model);
    /* Tanks will have different properties based on their model */

private:

    int speed;
    int power;
    int range;

    GamePlayer& commander;
    /* The GamePlayer that commands this tank */

};


#endif //SERVER_TANKPIECE_HPP
