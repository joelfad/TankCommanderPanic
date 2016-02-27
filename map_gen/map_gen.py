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
    tile_properties = [[(0,0) for j in range(map_properties["width"])] for i in range(map_properties["height"])]
    # tile_properties = {i: {j: (0,0) for j in range(map_properties["width"])} for i in range(map_properties["height"])}

    #DEBUG print tile properties
    if DEBUG is True:
        print("Tile properties:")
        [print(row) for row in tile_properties]

    # iterate through the layers
    for layer in root.findall("layer"):

        # get data string
        csv_data = layer.find("data").text

        # DEBUG print text
        if DEBUG is True:
            print("Layer csv data:")
            print(csv_data)

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
