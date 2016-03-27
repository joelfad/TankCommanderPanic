/*
 * Project: Tank Commander Panic
 * File: gameplayer.hpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#ifndef SERVER_GAMEPLAYER_HPP
#define SERVER_GAMEPLAYER_HPP

#include <string>

class GamePlayer {
public:

    GamePlayer(std::string name);

    const std::string &getName() const { return name; }
    /* Display name of player */

    int getId() const { return id; }

    int getAmmo() const { return ammo; }
    void setAmmo(int ammo) { GamePlayer::ammo = ammo; }
    /* Ammo is shared for the player's tanks */

    int getDeaths() const { return deaths; }
    void death() { GamePlayer::deaths--; }
    /* Number of tanks lost */

private:

    static int count;
    /* counter for assigning unique ids */

    std::string name;       // Display Name
    int id;                 // Id
    int ammo;               // Ammo count
    int deaths;             // Number of tanks lost

};


#endif //SERVER_GAMEPLAYER_HPP
