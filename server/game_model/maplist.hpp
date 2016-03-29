/*
 * Project: Tank Commander Panic
 * File: maplist.hpp
 * Author: Kurtis Jantzen
 * Description: List of maps, ids, and versions.
 */

#ifndef SERVER_MAPLIST_HPP
#define SERVER_MAPLIST_HPP

#include <string>
#include <vector>

#include "../protocol/protocoldefs.hpp"

//~declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace game_model {

namespace map_list {

constexpr std::string map_dir_path = "../resources/graphics/maps/";
/* path to directory where .map files are stored */

// lists of maps' IDs, versions, and names; vectors are aligned
constexpr std::vector<protocol::MapID> map_ids = {1, 2};
constexpr std::vector<protocol::MapVersion> map_versions = {1, 1};
constexpr std::vector<std::string> map_names = {"Test", "Fourbase"};

auto map_id_from_name(std::string map_name) -> protocol::MapID;
/* Get the map's ID from its name. If there's no match, return -1. */

auto map_version_from_id(protocol::MapID) -> protocol::MapVersion;
/* Get the map's latest version from its ID. If there's no match, return -1. */

auto map_file_path(protocol::MapID map_id, protocol::MapVersion map_version, std::string map_name) -> std::string;
auto map_file_path(std::string map_name) -> std::string;
/* Get the path to the .map file for a given map */

}

}


//~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto game_model::map_list::map_id_from_name(std::string map_name) -> protocol::MapID {
    for (int i = 0; i < map_names.size(); i++) {
        if (map_name == map_names[i])
            return map_ids[i];
    }
    return -1;
}

auto game_model::map_list::map_version_from_id(protocol::MapID map_id) -> protocol::MapVersion {
    for (int i = 0; i < map_ids.size(); i++) {
        if (map_id == map_ids[i])
            return map_versions[i];
    }
    return -1;
}

auto game_model::map_list::map_file_path(std::string map_name) -> std::string {
    auto map_id = map_id_from_name(map_name);
    auto map_version = map_version_from_id(map_id);
    return map_file_path(map_id, map_version, map_name);
}

auto game_model::map_list::map_file_path(protocol::MapID map_id, protocol::MapVersion map_version,
                                         std::string map_name) {
    std::string path = map_dir_path << map_id << "_" << map_version << "_" < map_name << ".map";
    return path;
}

#endif //SERVER_MAPLIST_HPP
