# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: battlefield.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 31, 2016

import sfml as sf
from numpy import swapaxes
from gamepiece import *
import const
Tile = sf.Sprite

class BattleField:

    # initialize the battlefield
    def __init__(self, game):
        self.game = game
        # TODO: Load map id and map version from Game State Message instead of "const"
        texture_data, map_data = self.load_map_file(const.id, const.version)
        self.texture = game.load_texture(texture_data)
        self.create_map(map_data)
        self.pieces = {}

        # load mock tanks
        for piece in const.fourbase_tanks:  # TODO: Remove and generate from Create Piece Message
            self.create_piece(*piece)       #

    # load map data from file
    def load_map_file(self, id, version):
        # load mock map properties
        self.tilewidth = const.tilewidth        # TODO: Remove when function is implemented
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

    # create map from loaded data
    def create_map(self, map_data):
        # rotate map data from [z][x][y] to [z][y][x]
        map_data = swapaxes(map_data, 1, 2).tolist()

        # generate map (from map data) to store battlefield tiles
        self.map = []
        for layer_data in map_data:
            layer = []
            for x, col_data in enumerate(layer_data):
                col = []
                for y, tile_id in enumerate(col_data):
                    if tile_id:             # a tile is found (non-zero tile_id)
                        tile = Tile(self.texture)
                        tile.texture_rectangle = self.game.get_texture_rect(tile_id)
                        tile.position = (x * self.tilewidth, y * self.tileheight)
                        col.append(tile)    # add new tile to column
                if col:
                    layer.append(col)       # add column to layer if not empty
            self.map.append(layer)          # add layer to battlefield map

    # get piece with given id
    def get_piece(self, id):
        return self.pieces[id]

    # create new gamepiece
    def create_piece(self, id, x, y, type, value):
        piece = GamePiece(id, (x * self.tilewidth, y * self.tileheight), type, value, self.game.texturehandler)
        self.pieces[id] = piece

    # destroy gamepiece
    def destroy_piece(self, id):
        del self.pieces[id]

    # draw the battlefield
    def draw(self):
        for z, layer in enumerate(self.map):
            for col in layer:
                for tile in col:
                    self.game.window.draw(tile)
            if z == self.piece_layer:
                self.draw_pieces()

    # draw game pieces
    def draw_pieces(self):
        for piece in self.pieces.values():
            self.game.window.draw(piece)
