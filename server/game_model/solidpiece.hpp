/*
 * Project: Tank Commander Panic
 * File: solidpiece.hpp
 * Author: Kurtis Jantzen
 * Description: Abstract solid game piece model that can take damage.
 */

#ifndef SERVER_SOLIDPIECE_HPP
#define SERVER_SOLIDPIECE_HPP


#include "gamepiece.hpp"

class SolidPiece: public GamePiece {
public:

    SolidPiece(int max_health);

    void collide(TankPiece& tank) override;

    void shot(int damage) override;
    /* react to taking damage */

protected:

    int health;
    /* Amount of damage that can be sustained */

    int max_health;
    /* Maximum value of health */

};


#endif //SERVER_SOLIDPIECE_HPP
