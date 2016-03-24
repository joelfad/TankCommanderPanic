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

    void shot(int damage) override;
    /* react to taking damage */

private:

    int health;
    /* Amount of damage that can be sustained */

    int clearshot;
    int cleardrive;

};


#endif //SERVER_SOLIDPIECE_HPP
