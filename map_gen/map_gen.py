#!/usr/bin/python3

import sys
import os
import xml.etree.ElementTree as ET

# set DEBUG flag
DEBUG = False

"""Parse a .tmx file and produce a .map file for the server to load."""
def generate(input_file_name):
    # parse the .tmx file into an XML tree
    tree = ET.parse(input_file_name)
    print("Parsing ", input_file_name, "...")

    # get the tree's root: the map tag
    root = tree.getroot()

    # get the properties of the map
    properties = root.find("properties")

    # create a dictionary for the properties
    map_properties = {}

    # add map element attributes
    map_properties["width"] = int(root.attrib["width"])
    map_properties["height"] = int(root.attrib["height"])

    # iterate over the properties
    for ppty in properties:
        map_properties[ppty.attrib["name"]] = ppty.attrib["value"]

    # DEBUG print the map properties
    if DEBUG is True:
        print("Map properties:")
        for ppty, value in map_properties.items():
            print(ppty, ": ", value, sep="")

    # initialize a 2D array for the tile properties
    tile_properties = [[(True, True) for j in range(map_properties["width"])] for i in range(map_properties["height"])]

    # DEBUG print tile properties
    if DEBUG is True:
        print_tiles(tile_properties)

    # iterate through the layers
    for layer in root.findall("layer"):

        # get data string
        csv_data = layer.find("data").text.strip()

        # get layer properties
        properties = layer.find("properties")

        # skip the layer if it has no game properties
        if properties is None:
            continue

        # create a dictionary for the layer properties
        layer_properties = {}

        # iterate over the properties
        for ppty in properties:
            layer_properties[ppty.attrib["name"]] = ppty.attrib["value"]

        # parse the properties
        cleardrive = (layer_properties["cleardrive"].find("true") >= 0)
        clearshot = (layer_properties["clearshot"].find("true") >= 0)

        # make a tuple out of the properties
        layer_tuple = (cleardrive, clearshot)

        # DEBUG print layer data
        if DEBUG is True:
            print()
            print("cleardrive:", layer_properties["cleardrive"])
            print("clearshot:", layer_properties["clearshot"])
            print(layer_tuple)
            print(csv_data)

        # iterate through the layer's tiles
        i, j = 0, 0
        for tile in csv_data.split(","):

            # if the tile is not empty on this layer
            if tile.strip() is not "0":

                # add tile's properties to tile_properties
                tile_properties[i][j] = combine(tile_properties[i][j], layer_tuple)

            # iterate through the rows of tile_properties correctly
            j += 1
            if j >= map_properties["width"]:
                j = 0
                i += 1

        # DEBUG print tile properties
        if DEBUG is True:
            print_tiles(tile_properties)

    # create the output .map file name
    output_file_name = input_file_name[:-3] + "map"

    # print the output file name
    print("Saving", output_file_name, "...")

    # open the output file
    with open(output_file_name, "w") as output_file:

        # write the maps's name
        output_file.write(map_properties["name"])
        output_file.write("\n")

        # write the maps's id
        output_file.write(map_properties["id"])
        output_file.write("\n")

        # write the maps's version
        output_file.write(map_properties["version"])
        output_file.write("\n")

        # write the maps's number of players
        output_file.write(map_properties["players"])
        output_file.write("\n")

        # write the maps's width
        output_file.write(str(map_properties["width"]))
        output_file.write("\n")

        # write the maps's height
        output_file.write(str(map_properties["height"]))
        output_file.write("\n")

        # write the tile properties
        output_file.write("\n")
        for row in tile_properties:
            for tile in row:
                output_file.write(tilechar(tile))
            output_file.write("\n")

"""Combine the properties of two layers for a given tile."""
def combine(existing, new):
    # if there's a new ground layer (like a bridge) overwrite
    if new == (True, True):
        return (True, True)

    # AND the properties together to get the result
    return (existing[0] and new[0], existing[1] and new[1])

""""Represent a tile's properties as a character for output."""
def tilechar(tile):
    result = 48 # offset
    if tile[0]:
        result += 2
    if tile[1]:
        result += 1
    return str(chr(result))

"""Represent the properties of the map tiles nicely."""
def print_tiles(tile_properties):
    print("Tile properties:")
    for row in tile_properties:
        for tile in row:
            if tile == (True, True):
                print(".", end="")
            elif tile == (False, True):
                print("~", end="")
            elif tile == (True, False):
                print("#", end="")
            elif tile == (False, False):
                print("@", end="")
        print()

if __name__ == "__main__":

    # create a list of files to generate
    gen_queue = []

    # enforce argument count
    if len(sys.argv) >= 2:

        # iterate over arguments
        for arg in sys.argv[1:]:

            # check for debug flag
            if arg == "--debug":
                DEBUG = True
                continue

            # make sure it's a .tmx file
            if arg.endswith(".tmx"):

                # make sure it's a real file
                if os.path.isfile(arg):

                    # add to queue
                    gen_queue.append(arg)

                else:
                    # print error message
                    print("File, ", arg, ", not found")

            else:
                # print usage clarification
                print("File, ", arg, ", is not a .tmx file.")

    else:
        # print usage message
        print("Usage: map_gen.py <tmx-map-file-path> [--debug]")

    # iterate over queued input files
    for input_file_name in gen_queue:

        # generate the server's map file
        generate(input_file_name)
