# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: battlefield.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 4, 2016

import sfml as sf
from numpy import swapaxes
from gamepiece import *
from gamestate import GameState as gs
import import_tmx
import const
Tile = sf.Sprite

class BattleField:

    # initialize the battlefield
    def __init__(self, game, map_id, map_version):
        self.game = game
        texture_data, map_data = self.load_map_file(map_id, map_version)
        self.texture = game.load_texture(texture_data)
        self.mapwidth, self.mapheight, map_ = self.create_map(map_data)
        self.prerender(map_)
        self.pieces = {}

    # load map data from file
    def load_map_file(self, id_, version):
        (
            self.map_name,
            self.map_tiles_x,
            self.map_tiles_y,
            self.piece_layer,
            texture_data
        ), map_data = import_tmx.load_map_file(id_, version)

        self.tilewidth, self.tileheight = texture_data[1:3]
        print("Piece Layer: {}".format(self.piece_layer))

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
    def create_piece(self, type_, id_, x, y, value):
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
        del self.pieces[id_]

    # draw the battlefield
    def draw(self):
        self.game.window.draw(self.map_bottom)
        self.draw_pieces()
        self.game.window.draw(self.map_top)

    # draw game pieces
    def draw_pieces(self):
        for piece in self.pieces.values():
            self.game.window.draw(piece)
