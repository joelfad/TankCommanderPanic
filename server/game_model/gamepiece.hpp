/*
 * Project: Tank Commander Panic
 * File: gamepiece.hpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#ifndef SERVER_GAMEPIECE_HPP
#define SERVER_GAMEPIECE_HPP


class GamePiece {

public:

    GamePiece();

    virtual void collide(TankPiece tank);
    /* react to being collided into by tank (after occupying the same square) */

    virtual void shot(int damage);
    /* react to taking damage */

    int getId() const { return id; }

    bool isClearshot() const { return clearshot; }
    /* designates that the piece can be fired through, otherwise a round impacts on the piece */

    bool isCleardrive() const { return cleardrive; }
    /* designates that the piece can be driven on, otherwise the piece blocks movement */

private:

    static int count = 0;
    /* counter for assigning unique ids */

    int id;
    bool clearshot;
    bool cleardrive;

};


#endif //SERVER_GAMEPIECE_HPP
