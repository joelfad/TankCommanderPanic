/*
 * Project: Tank Commander Panic
 * File: gameplayer.hpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#ifndef SERVER_GAMEPLAYER_HPP
#define SERVER_GAMEPLAYER_HPP

#include <string>

#include "../protocoldefs.hpp"

class GamePlayer {
public:

    GamePlayer(std::string name);

    const std::string &getName() const { return name; }
    /* display name of player */

    auto getId() const noexcept { return id; }

    auto getAmmo() const  noexcept { return ammo; }
    void setAmmo(int ammo) { GamePlayer::ammo = ammo; }
    /* ammo is shared for the player's tanks */

    auto getTankCount() const { return tank_count; }
    /* number of tanks */

    void looseTank() { GamePlayer::tank_count--; }
    /* register a loss of a tank */

private:

    static protocol::PlayerID next_id;
    /* counter for assigning unique ids */

    std::string name;               // Display Name
    protocol::PlayerID id;          // Id
    int ammo;                       // Ammo next_id
    protocol::TankCount tank_count; // Number of tanks

};


#endif //SERVER_GAMEPLAYER_HPP
