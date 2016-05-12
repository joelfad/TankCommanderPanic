# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: texturehandler.py
# Author: Joel McFadden
# Created: March 29, 2016
# Modified: April 4, 2016

import sfml as sf

class TextureHandler:
    GRAPHICS_DIR = "resources/graphics/"

    def __init__(self, image_source, tilewidth, tileheight, tilecount, columns):
        self.load_texture(image_source)
        self.tilewidth = tilewidth
        self.tileheight = tileheight
        self.tilecount = tilecount
        self.columns = columns

    # load texture data from file
    def load_texture(self, filename):
        try:
            self.texture = sf.Texture.from_file(self.GRAPHICS_DIR + filename)
        except IOError:
            print("Unable to load battlefield texture from {}".format(filename))
            raise

    # calculates the location of a tile in the texture file from its id
    def get_rect(self, tile_id):
        # check for valid id
        if tile_id > self.tilecount:
            raise ValueError("Invalid tile id: {}".format(tile_id))

        # calculate offset in texture
        left = ((tile_id - 1) % self.columns) * self.tilewidth
        top = ((tile_id - 1) // self.columns) * self.tileheight

        return sf.Rect((left, top), (self.tilewidth, self.tileheight))
