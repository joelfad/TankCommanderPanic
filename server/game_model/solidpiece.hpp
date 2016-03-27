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

    SolidPiece();
    SolidPiece(int max_health);

    void set_max_health(int max_health);
    /* sets max_health and sets to full health */

    void collide(TankPiece& tank) override;

    void shot(int damage) override;
    /* react to taking damage */

protected:

    int health;
    /* amount of damage that can be sustained */

    int max_health;
    /* maximum value of health */

};


#endif //SERVER_SOLIDPIECE_HPP
