#!/usr/bin/python3
# load map data from file
import os
import tmx

def load_map_file(id_, version):
    maps_directory = "../resources/graphics/maps"
    filepathbeginning = str(id_) + '_' + str(version)
    filepathend = '.tmx'
    map_found = False
    map_file = None
    for file_name in os.listdir(maps_directory):
        if file_name.startswith(filepathbeginning) and file_name.endswith(filepathend):
            map_found = validate_map_version(maps_directory, file_name, id_, version, map_found)
            if map_found == True:
                map_file = file_name

    if map_file == None:
        raise FileNotFoundError("Map with id " + str(id_) + " and version " + str(version) + " cannot be found.")
    else:
        read_map_file(map_file)

def validate_map_version(maps_directory, filename, id_, version, map_found):
    #check version information
    file_path = maps_directory + '/' + filename
    map = tmx.TileMap.load(file_path)
    map_version = int(float(map.version))

    #check id information
    map_id = None;
    properties = map.properties
    for map_property in properties:
        if map_property.name == 'id':
            map_id = int(float(map_property.value));
    #if map is valid
    if map_version == version and map_id == id_:
        if map_found == True:
            raise RuntimeError("Duplicate map files found.")
        else:
            return True;
    #if map is invalid
    else:
        return False;

def read_map_file(mapfile):


    '''
    # load mock map properties
    self.map_tiles_x = const.width          # TODO: Remove when function is implemented
    self.map_tiles_y = const.height         #
    self.tilewidth = const.tilewidth        #
    self.tileheight = const.tileheight      #
    self.piece_layer = const.piece_layer    #

    texture_data = (                        # TODO: Remove "const" when function is implemented
                 const.image_source,      #
                 self.tilewidth,
                 self.tileheight,
                 const.tilecount,         #
                 const.columns,           #
                 )

    # load mock map data
    map_data = const.fourbase_tile_ids  # TODO: Remove when function is implemented
    return (texture_data, map_data)
    '''

if __name__ == "__main__":
    load_map_file(2,1)
