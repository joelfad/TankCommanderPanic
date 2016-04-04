# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: fonthandler.py
# Author: Joel McFadden
# Created: April 4, 2016
# Modified: April 4, 2016

import sfml as sf

class FontHandler:
    FONTS_DIR = "resources/fonts/"
    FONTNAME = "atarcc.ttf"

    def __init__(self):
        self.load_font(self.FONTNAME)

    # load font from file
    def load_font(self, filename):
        try:
            self.font = sf.Font.from_file(self.FONTS_DIR + filename)
        except IOError:
            print("Unable to load font from {}".format(filename))
            raise
