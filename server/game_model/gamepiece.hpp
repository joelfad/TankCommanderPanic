/*
 * Project: Tank Commander Panic
 * File: gamepiece.hpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#ifndef SERVER_GAMEPIECE_HPP
#define SERVER_GAMEPIECE_HPP

#include "../protocoldefs.hpp"

class TankPiece;

class GamePiece {

public:

    GamePiece(bool clear_shot, bool clear_drive);

    virtual void collide(TankPiece& tank) = 0;
    /* react to being collided into by tank (after occupying the same square) */

    virtual void shot(int damage) = 0;
    /* react to taking damage */

    auto get_id() const noexcept { return id; }

    auto is_clear_shot() const noexcept { return clear_shot; }
    /* designates that the piece can be fired through, otherwise a round impacts on the piece */

    auto is_clear_drive() const noexcept { return clear_drive; }
    /* designates that the piece can be driven on, otherwise the piece blocks movement */

    virtual ~GamePiece() noexcept {}

protected:

    static protocol::PieceID next_id;
    /* counter for assigning unique ids */

    protocol::PieceID id;
    bool clear_shot;
    bool clear_drive;

};


#endif //SERVER_GAMEPIECE_HPP
