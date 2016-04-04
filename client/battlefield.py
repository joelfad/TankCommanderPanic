# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: battlefield.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 3, 2016

import sfml as sf
from numpy import swapaxes
from gamepiece import *
from gamestate import GameState as gs
import const
Tile = sf.Sprite

class BattleField:

    # initialize the battlefield
    def __init__(self, game):
        self.game = game
        # TODO: Load map id and map version from Game State Message instead of "const"
        texture_data, map_data = self.load_map_file(const.id_, const.version)
        self.texture = game.load_texture(texture_data)
        self.mapwidth, self.mapheight, map_ = self.create_map(map_data)
        self.prerender(map_)
        self.pieces = {}

        # load mock tanks
        for piece in const.fourbase_tanks:  # TODO: Remove and generate from Create Piece Message
            self.create_piece(*piece)       #

    # load map data from file
    def load_map_file(self, id_, version):
        # load mock map properties
        self.map_tiles_x = const.width          # TODO: Remove when function is implemented
        self.map_tiles_y = const.height         #
        self.tilewidth = const.tilewidth        #
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
        map_ = []
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
            map_.append(layer)               # add layer to battlefield map

        # map width and height (in pixels) and map
        return (self.map_tiles_x * self.tilewidth, self.map_tiles_y * self.tileheight, map_)

    # optimize drawing by flattening layers below and above gamepieces
    def prerender(self, map_):
        # create textures for pre-rendering
        self.top_layers = sf.RenderTexture(self.mapwidth, self.mapheight)
        self.bottom_layers = sf.RenderTexture(self.mapwidth, self.mapheight)

        # render map tiles on the textures
        for z, layer in enumerate(map_):
            for col in layer:
                for tile in col:
                    if z > self.piece_layer:
                        self.top_layers.draw(tile)
                    else:
                        self.bottom_layers.draw(tile)

        # update textures
        self.top_layers.display()
        self.bottom_layers.display()

        # set sprites
        self.map_top = sf.Sprite(self.top_layers.texture)
        self.map_bottom = sf.Sprite(self.bottom_layers.texture)

    # get piece with given id
    def get_piece(self, id_):
        return self.pieces[id_]

    # create new gamepiece
    def create_piece(self, id_, x, y, type_, value):
        piece = GamePiece(id_, (x * self.tilewidth, y * self.tileheight), type_, value, self.game.texturehandler)
        self.pieces[id_] = piece

    # destroy gamepiece
    def destroy_piece(self, id_):
        piece = self.pieces[id_]
        # check for destroyed tank
        if piece in self.game.tanks:                # piece is player's tank
            self.game.tanks.remove(piece)
            if self.game.tanks:                     # piece is not last tank
                if piece is self.game.active_tank:  # piece is active tank
                    self.game.active_tank = self.game.tanks[0]
            else:                                   # piece is last tank
                self.game.state = gs.lose
        # destroy
        del piece

    # draw the battlefield
    def draw(self):
        self.game.window.draw(self.map_bottom)
        self.draw_pieces()
        self.game.window.draw(self.map_top)

    # draw game pieces
    def draw_pieces(self):
        for piece in self.pieces.values():
            self.game.window.draw(piece)
