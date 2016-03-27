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

class TankPiece : public SolidPiece {
public:

    TankPiece(GamePlayer& commander);
    /* Tank with default properties */

    // TankPiece(GamePlayer commander, int model);
    /* Tanks will have different properties based on their model */

private:

    int health;
    int speed;
    int power;
    int range;

    GamePlayer& commander;
    /* The GamePlayer that commands this tank */

};


#endif //SERVER_TANKPIECE_HPP
