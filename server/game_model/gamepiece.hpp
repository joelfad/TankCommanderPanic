/*
 * Project: Tank Commander Panic
 * File: gamepiece.hpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#ifndef SERVER_GAMEPIECE_HPP
#define SERVER_GAMEPIECE_HPP

class TankPiece;

class GamePiece {

public:

    GamePiece(bool clearshot, bool cleardrive);

    virtual void collide(TankPiece& tank) = 0;
    /* react to being collided into by tank (after occupying the same square) */

    virtual void shot(int damage) = 0;
    /* react to taking damage */

    int getId() const noexcept { return id; }

    bool isClearshot() const noexcept { return clearshot; }
    /* designates that the piece can be fired through, otherwise a round impacts on the piece */

    bool isCleardrive() const noexcept { return cleardrive; }
    /* designates that the piece can be driven on, otherwise the piece blocks movement */

    virtual ~GamePiece() noexcept {}

protected:

    static int count;
    /* counter for assigning unique ids */

    int id;
    bool clearshot;
    bool cleardrive;

};


#endif //SERVER_GAMEPIECE_HPP
