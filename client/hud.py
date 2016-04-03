# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: hud.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 2, 2016

import sfml as sf
from gamestate import GameState as gs
from gamepiece import PieceType as pt
from numpy import swapaxes, clip
import const

class HUD:

    def __init__(self, game):
        self.game = game
        self.texture = game.texturehandler.texture

        # load map properties and tank data
        self.map_properties = self.load_properties()
        self.tank_data = const.tank_data

        # set useful values for calculations
        self.centerview = (game.window.size.x * 0.5 * game.window.view.viewport.width,
                           game.window.size.y * 0.5 * game.window.view.viewport.height)
        self.tilewidth = game.texturehandler.tilewidth
        self.tileheight = game.texturehandler.tileheight
        self.min_x = 0.5 * self.tilewidth
        self.min_y = 0.5 * self.tileheight
        self.max_x = game.battlefield.mapwidth - (self.tilewidth * 0.5)
        self.max_y = game.battlefield.mapheight - (self.tileheight * 0.5)
        self.max_x_index = len(self.map_properties) - 1
        self.max_y_index = len(self.map_properties[0]) - 1

        # load hud sprites
        self.sprites = {}
        for key, val in const.hud_sprites.items():
            s = sf.Sprite(self.texture)
            s.texture_rectangle = game.get_texture_rect(val)
            s.origin = (s.texture_rectangle.width / 2, s.texture_rectangle.height / 2)
            self.sprites[key] = s

        # initialize values
        self.update()

    def update(self):
        # update range of active tank
        center = self.game.active_tank.position
        active_x, active_y = self.game.active_tank.coord()
        active_tank_data = self.tank_data[self.game.active_tank.type]
        max_range = active_tank_data[1]

        if self.game.state is gs.play:
            # set range
            self.sprites["center"].position = center
            # self.sprites["north"].position  = self.offset(center, 0, -max_range)

            # get set of pieces that are tanks or bricks
            pieces_x = {
                        p for p in self.game.battlefield.pieces.values()
                        if p.coord()[1] is active_y
                        and (p.type in pt.tank.value or p.type in pt.brick.value)
                        }
            pieces_y = {
                        p for p in self.game.battlefield.pieces.values()
                        if p.coord()[0] is active_x
                        and (p.type in pt.tank.value or p.type in pt.brick.value)
                        }

            # calculate east range
            clear_east = 1   # 1 if max range is reached
            for x in range(active_x + 1, active_x + max_range + 1):
                if not self.map_properties[clip(x, 0, self.max_x_index)][active_y] % 2:
                    clear_east = 0   # 0 if blocked by obstacle
                    break
            for px in pieces_x:
                if px.coord()[0] in range(active_x + 1, x + 1):
                    if px.coord()[0] <= x:
                        x = px.coord()[0]
                        clear_east = 1   # 1 if gamepiece is in range
            x = (x - 0.5 + clear_east) * self.tilewidth
            self.sprites["east"].position = self.offset(x, center.y)

        elif self.game.state is gs.pan:
            # set crosshair
            self.sprites["pan"].position    = self.game.window.map_pixel_to_coords(self.centerview)

    def offset(self, x, y):
        return (clip(x, self.min_x, self.max_x),
                clip(y, self.min_y, self.max_y))

    def load_properties(self):
        return swapaxes(const.fourbase_properties, 0, 1).tolist()

    def draw(self):
        if self.game.state is gs.play:
            # draw range
            self.game.window.draw(self.sprites["center"])
            self.game.window.draw(self.sprites["north"])
            self.game.window.draw(self.sprites["east"])
            self.game.window.draw(self.sprites["south"])
            self.game.window.draw(self.sprites["west"])
        elif self.game.state is gs.pan:
            # draw crosshair
            self.game.window.draw(self.sprites["pan"])
