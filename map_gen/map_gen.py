import sys
import os
import xml.etree.ElementTree as ET

# set DEBUG flag
DEBUG = True

"""Parse a .tmx file and produce a file for the server to load as a map."""
def main():
    # parse the .tmx file into an XML tree
    tree = ET.parse(sys.argv[1])
    print("Parsing ", sys.argv[1], "...")

    # get the tree's root: the map tag
    root = tree.getroot()

    # get the properties of the map
    properties = root.find("properties")

    # a dictionary for the properties
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

    # a 2D array for the tile properties
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

        # a dictionary for the layer properties
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
            if tile.strip() is not "0":

                # add tile's properties to tile_properties
                tile_properties[i][j] = combine(tile_properties[i][j], layer_tuple)

            j += 1
            if j >= map_properties["width"]:
                j = 0
                i += 1

        # DEBUG print tile properties
        if DEBUG is True:
            print_tiles(tile_properties)

def combine(existing, new):
    # if there's a new ground layer (like a bridge) overwrite
    if new is (True, True):
        return (True, True)

    # AND the properties together to get the result
    return (existing[0] and new[0], existing[1] and new[1])

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

    # enforce argument count
    if len(sys.argv) is 2:

        # make sure it's a .tmx file
        if sys.argv[1].endswith(".tmx"):

            # make sure it's a real file
            if os.path.isfile(sys.argv[1]):

                # generate the server's map file
                main()

            else:
                # print error message
                print("File, ", sys.argv[1], ", not found")

        else:
            # print usage clarification
            print("File, ", sys.argv[1], ", is not a .tmx file.")

    else:
        # print usage message
        print("Usage: map_gen <tmx-map-file-path>")
