/*
 * Project: Tank Commander Panic
 * File: tile.hpp
 * Author: Kurtis Jantzen
 * Description: Models an unchanging square on the map.
 */

#ifndef SERVER_TILE_HPP
#define SERVER_TILE_HPP


class Tile {
public:

    Tile(char property_code);

    // --getters--

    bool isClearShot() const noexcept { return clear_shot; }
    /* designates that the tile can be fired through, otherwise a round impacts on the tile */

    bool isClearDrive() const noexcept { return clear_drive; }
    /* designates that the tile can be driven on, otherwise the tile blocks movement */

private:

    bool clear_shot;
    bool clear_drive;

};


#endif //SERVER_TILE_HPP
