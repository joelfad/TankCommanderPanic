/*
 * Project: Tank Commander Panic
 * File: gameplayer.hpp
 * Author: Kurtis Jantzen
 * Description: Models a player of the game.
 */

#ifndef SERVER_GAMEPLAYER_HPP
#define SERVER_GAMEPLAYER_HPP

#include <string>

#include "../protocol/protocoldefs.hpp"

namespace game_model {

class GamePlayer {
public:

    GamePlayer();

    GamePlayer(GamePlayer&& other);

    GamePlayer& operator=(GamePlayer&& rhs);

    static GamePlayer make_game_player();

    const std::string &get_name() const noexcept { return this->name; }
    void set_name(std::string name) { this->name = name; }
    /* display name of player */

    auto get_id() const noexcept { return this->id; }

    auto get_ammo() const noexcept { return ammo; }
    void set_ammo(int ammo) { this->ammo = ammo; }
    void change_ammo(int diff) { this->ammo += diff; }
    /* ammo is shared for the player's tanks */

    auto get_tank_count() const noexcept { return this->tank_count; }
    /* number of tanks */

    void loose_tank() { this->tank_count--; }
    /* register a loss of a tank */

    auto get_team_color() const noexcept { return this->team_color; }

private:

    static protocol::PlayerID next_id;
    /* counter for assigning unique ids */

    static constexpr protocol::PlayerID invalid_id = 0;

    std::string name;                   // Display Name
    protocol::PlayerID id = invalid_id; // Id
    int ammo;                           // Ammo next_id
    protocol::TankCount tank_count;     // Number of tanks
    protocol::TeamColor team_color;     // Team color

};

}

#endif //SERVER_GAMEPLAYER_HPP
