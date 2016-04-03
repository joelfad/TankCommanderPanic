# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: hud.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 2, 2016

import sfml as sf
from gamestate import GameState as gs
from numpy import swapaxes
import const

class HUD:
    # texture : Texture

    def __init__(self, game):
        self.game = game
        self.texture = game.texturehandler.texture
        self.centerview = (game.window.size.x * 0.5 * game.window.view.viewport.width,
                           game.window.size.y * 0.5 * game.window.view.viewport.height)
        self.tilewidth = game.texturehandler.tilewidth
        self.tileheight = game.texturehandler.tileheight
        self.map_properties = self.load_properties()
        self.tank_map = const.tank_map

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
        active_tank_data = self.tank_map[self.game.active_tank.type]
        max_range = active_tank_data[1]

        if self.game.state is gs.play:
            # set range
            self.sprites["center"].position = center
            self.sprites["north"].position  = self.offset(center, 0, -max_range)
            self.sprites["east"].position   = self.offset(center,  max_range, 0)
            self.sprites["south"].position  = self.offset(center, 0,  max_range)
            self.sprites["west"].position   = self.offset(center, -max_range, 0)
        elif self.game.state is gs.pan:
            # set crosshair
            self.sprites["pan"].position    = self.game.window.map_pixel_to_coords(self.centerview)

    def offset(self, coord, x, y):
        return (coord.x + (x * self.tilewidth), coord.y + (y * self.tileheight))

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
