# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: import_tmx.py
# Author: Marissa Baden
# Created: April 3, 2016
# Modified: April 4, 2016

import os
import xml.etree.ElementTree as ET
import csv

MAP_DIRECTORY = "../resources/graphics/maps"

def load_map_file(id_, version):
    global MAP_DIRECTORY

    # choose file name beginning and end
    filepathbeginning = str(id_) + '_' + str(version)
    filepathend = '.tmx'
    # iterate through all files in MAP_DIRECTORY
    found = False
    filename = None
    for f in os.listdir(MAP_DIRECTORY):
        # look for file with the format filepathbeginning*filepathend
        if f.startswith(filepathbeginning) and f.endswith(filepathend):
            # check if the map is valid
            found = validate_map_version(MAP_DIRECTORY + '/' + f, id_, version, found)
            if found:
                filename = f

    if not filename:
        # if there are no valid map files
        raise FileNotFoundError("Map with id " + str(id_) + " and version " + str(version) + " cannot be found.")
    else:
        # read valid map
        return read_map_file(MAP_DIRECTORY + '/' + filename)

def validate_map_version(path, id_, version, found):
    # parse the .tmx file into an XML tree
    tree = ET.parse(path)
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
        if found == True:
            raise RuntimeError("Duplicate map files found.")
        else:
            found = True;
    #if map is invalid
    else:
        found = False;

    return found

def read_map_file(path):
    # parse the .tmx file into an XML tree
    tree = ET.parse(path)

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
    directory, image_source = os.path.split(image.attrib['source'])

    # get the properties of the map
    properties = root.find('properties')
    for p in properties:
        # get name of map
        if "name" in p.attrib['name']:
            map_name = str(p.attrib['value'])

    # create list for layers
    map_data = []

    piece_layer = None  # TODO: Check for errors (None is invalid)
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

        # add new layer to map_data
        if skip_layer is False:
            # make list for layer
            layer_list = []

            # get data
            csv_data = layer.find("data").text.strip()

            # split data by rows
            for row in csv_data.split('\n'):
                row = row.strip()
                row_list = []
                for tile in row.split(','):
                    tile = tile.strip()
                    if(tile == ''):
                        continue
                    tile = int(tile)
                    row_list.append(tile)
                layer_list.append(row_list)
            map_data.append(layer_list)
            layer_counter += 1

        # if this is the piece layer, record what layer index is below it
        else:
            piece_layer = layer_counter - 1
            skip_layer = False

    parsed_data = \
    (
        map_name,
        map_tiles_x,
        map_tiles_y,
        piece_layer,
        (
            image_source,
            tilewidth,
            tileheight,
            tilecount,
            columns
        )
    )

    return (parsed_data, map_data)
