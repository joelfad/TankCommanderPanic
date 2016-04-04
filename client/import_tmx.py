#!/usr/bin/python3
# load map data from file
import os
import tmx

MAPS_DIRECTORY = '';
MAP_FOUND = False;
MAP_FILE = None;

def load_map_file(id_, version):
    global MAPS_DIRECTORY, MAP_FOUND, MAP_FILE
    # define map directory
    MAPS_DIRECTORY = "../resources/graphics/maps"
    # choose file name beginning and end
    filepathbeginning = str(id_) + '_' + str(version)
    filepathend = '.tmx'
    # iterate through all files in maps_directory
    for file_name in os.listdir(MAPS_DIRECTORY):
        # look for file with the format filepathbeginning*filepathend
        if file_name.startswith(filepathbeginning) and file_name.endswith(filepathend):
            # check if the map is valid
            validate_map_version(file_name, id_, version)
            if MAP_FOUND == True:
                MAP_FILE = file_name

    if MAP_FILE == None:
        # if there are no valid map files
        raise FileNotFoundError("Map with id " + str(id_) + " and version " + str(version) + " cannot be found.")
    else:
        # read valid map
        read_map_file()

def get_map_property(map, name):
    for map_property in map.properties:
        if map_property.name == name:
            return map_property.value
    return None;

def validate_map_version(filename, id_, version):
    global MAP_FOUND
    # load the map file
    file_path = MAPS_DIRECTORY + '/' + filename
    map = tmx.TileMap.load(file_path)
    # get the map id from the map file
    map_id = int(float(get_map_property(map, 'id')))
    # get the map_version from the map file
    map_version = int(float(get_map_property(map, 'version')))
    # check if map is valid
    if map_id == id_ and map_version == version:
        # if a valid map was found before this, raise an exception
        if MAP_FOUND == True:
            raise RuntimeError("Duplicate map files found.")
        else:
            MAP_FOUND = True;
    #if map is invalid
    else:
        MAP_FOUND = False;

def read_map_file():
    map = tmx.TileMap.load(MAPS_DIRECTORY + '/' + MAP_FILE)
    # get dimensions of map in tiles
    map_tiles_x = map.width
    map_tiles_y = map.height
    # get dimensions of tiles
    tilewidth = map.tilewidth
    tileheight = map.tileheight
    # get name of map
    name = str(get_map_property(map, 'name'))


    '''
    # load mock map properties
    self.map_tiles_x = const.width          # TODO: Remove when function is implemented
    self.map_tiles_y = const.height         #
    self.tilewidth = const.tilewidth        #
    self.tileheight = const.tileheight      #
    self.piece_layer = const.piece_layer    #

    texture_data = (                        # TODO: Remove "const" when function is implemented
                 const.image_source,        #
                 self.tilewidth,
                 self.tileheight,
                 const.tilecount,           #
                 const.columns,             #
                 )

    # load mock map data
    map_data = const.fourbase_tile_ids  # TODO: Remove when function is implemented
    return (texture_data, map_data)
    '''

if __name__ == "__main__":
    load_map_file(2,1)
