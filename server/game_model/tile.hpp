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

    bool isClearshot() const { return clearshot; }
    /* designates that the tile can be fired through, otherwise a round impacts on the tile */

    bool isCleardrive() const { return cleardrive; }
    /* designates that the tile can be driven on, otherwise the tile blocks movement */

private:

    bool clearshot;
    bool cleardrive;

};


#endif //SERVER_TILE_HPP
