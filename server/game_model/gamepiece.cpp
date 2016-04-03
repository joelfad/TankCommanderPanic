/*
 * Project: Tank Commander Panic
 * File: gamepiece.cpp
 * Author: Kurtis Jantzen
 * Description: Abstract game piece model with unique ids.
 */

#include "gamepiece.hpp"
#include "gamemodelerror.hpp"

protocol::PieceID game_model::GamePiece::next_id = 1;
/* set initial next_id to 1 */

game_model::GamePiece::GamePiece(bool clear_shot, bool clear_drive) : clear_shot(clear_shot), clear_drive(clear_drive) {

    // assign id and increment next_id
    this->id = next_id++;
}

void game_model::GamePiece::collide(TankPiece &tank) {

    // if this driven over, it had better be clear to drive on
    if (!this->is_clear_drive())
        throw GameModelEventError("collision with non-collide-able (not clear-drive) game piece");
}

int game_model::GamePiece::shot(int damage) {

    // if this was shot, it had better not be clear to shoot through
    if (this->is_clear_shot())
        throw GameModelEventError("non-shoot-able (clear-shot) game piece was shot");

    return 0;
}
