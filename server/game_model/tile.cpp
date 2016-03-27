/*
 * Project: Tank Commander Panic
 * File: tile.cpp
 * Author: Kurtis Jantzen
 * Description: Models an unchanging square on the map.
 */

#include "tile.hpp"

Tile::Tile(char property_code) {

    // remove the offset to ascii '0'
    unsigned char normalized_code = static_cast<unsigned char>(property_code - '0');

    // assign values to parameters
    this->cleardrive = static_cast<bool>(0x2 & normalized_code);
    this->clearshot = static_cast<bool>(0x1 & normalized_code);
}

