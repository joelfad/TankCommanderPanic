#!/usr/bin/python3
# load map data from file
import os
import xml.etree.ElementTree as ET
import csv

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

def validate_map_version(filename, id_, version):
    global MAP_FOUND
    # load the map file
    file_path = MAPS_DIRECTORY + '/' + filename
    # parse the .tmx file into an XML tree
    tree = ET.parse(file_path)
    # get the tree's root: the map tag
    root = tree.getroot()
    # get the properties of the map
    properties = root.find('properties')

    for p in properties:
        # get the map id from the map file
        if "id" in p.attrib['name']:
            map_id = int(p.attrib['value'])
        # get the map version from the map file
        if "version" in p.attrib['name']:
            map_version = int(p.attrib['value'])

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
    # parse the .tmx file into an XML tree
    tree = ET.parse(MAPS_DIRECTORY + '/' + MAP_FILE)
    # get the tree's root: the map tag
    root = tree.getroot()

    # get dimensions of map in tiles
    map_tiles_x = int(root.attrib['width'])
    map_tiles_y = int(root.attrib['height'])
    # get dimensions of tiles
    tilewidth = int(root.attrib['tilewidth'])
    tileheight = int(root.attrib['tileheight'])

    # get the number of the columns
    tileset = root.find('tileset')
    columns = int(tileset.attrib['columns'])
    tilecount = int(tileset.attrib['tilecount'])

    # get image source
    image = tileset.find('image')
    image_source = image.attrib['source']

    # get name of map
    # get the properties of the map
    properties = root.find('properties')
    for p in properties:
        # get the map id from the map file
        if "name" in p.attrib['name']:
            map_name = str(p.attrib['value'])

    texture_data = (
                image_source,
                tilewidth,
                tileheight,
                tilecount,
                columns,
    )

    # error checking on map values
    print("map_tiles_x is " + str(map_tiles_x))
    print("map_tiles_y is " + str(map_tiles_y))
    print("tilewidth is " + str(tilewidth))
    print("tileheight is " + str(tileheight))
    print("columns is " + str(columns))
    print("tilecount is " + str(tilecount))
    print("image_source is " + str(image_source))
    print("map_name is " + str(map_name))

    # create list for layers
    map_data = []

    piece_layer = None
    layer_counter = 0
    # iterate through the layers
    for layer in root.findall("layer"):

        # check if game piece layer
        skip_layer = False
        properties = layer.find('properties')
        for p in properties:
            # get the game_pieces_placeholder from the map file
            if 'game_pieces_placeholder' in p.attrib['name']:
                skip_layer = True

        if skip_layer is False:
            # add new layer to map_data
            # make list for layer
            layer_list = []
            # get data
            csv_data = layer.find("data").text.strip()
            #print('clean csv ------------------------------------------')
            #print(csv_data)
            #print('end clean csv --------------------------------------')
            # split data by rows
            for row in csv_data.split('\n'):
                row = row.strip()
                #print('start row ------------------------------------------')
                #print(row)
                #print('end row --------------------------------------')
                row_list = []
                for tile in row.split(','):
                    tile = tile.strip()
                    if(tile == ''):
                        continue
                    #print('start tile ------------------------------------------')
                    #print(tile)
                    #print('end tile --------------------------------------')
                    tile = int(tile)
                    row_list.append(tile)
                layer_list.append(row_list)
            map_data.append(layer_list)
            layer_counter += 1
        else:
            # if this is the piece layer, record what layer index is below it
            piece_layer = layer_counter - 1
            skip_layer = False

        return (texture_data, map_data)

    '''
    for l in map_data:
        for r in l:
            for t in r:
                print("{:4d}".format(t), end="")
            print()
        print('\n')


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
