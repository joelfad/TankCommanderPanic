import sys
import os
import xml.etree.ElementTree as ET

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

    # iterate over the properties
    for ppty in properties:
        map_properties[ppty.attrib["name"]] = ppty.attrib["value"]

    # TEMP print the map properties
    print("Map properties:")
    for ppty, value in map_properties.items():
        print(ppty, ": ", value, sep="")

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
