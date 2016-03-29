/*
 * Project: Tank Commander Panic
 * File: gamemodel.cpp
 * Author: Kurtis Jantzen
 * Description: This class models the state of the game.
 */

#include "gamemodel.hpp"
#include "maplist.hpp"

game_model::GameModel::GameModel(std::string map_name) {

    // get the map's id from the name
    this->map_id = game_model::map_list::map_id_from_name(map_name);

    // get the latest version num of the map
    this->map_version = game_model::map_list::map_version_from_id(this->map_id);

    // TODO find .map file in ../resources/graphics/maps/ based on id and version
    std::string path = map_list::map_file_path(this->map_id, this->map_version, map_name);

    // TODO import .map data and populate fields
    // TODO create starting gamepieces based on map data
}
