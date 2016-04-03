# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: hud.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 3, 2016

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
        self.max_x = game.battlefield.map_tiles_x - 1
        self.max_y = game.battlefield.map_tiles_y - 1

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

        # set crosshair
        if self.game.state is gs.pan:
            self.sprites["pan"].position = self.game.window.map_pixel_to_coords(self.centerview)
        # set range
        elif self.game.state is gs.play:
            # get set of pieces that are tanks or bricks
            pieces_x = {
                        p for p in self.game.battlefield.pieces.values()
                        if p.coord().y is active_y
                        and (p.type in pt.tank.value or p.type in pt.brick.value)
                        }
            pieces_y = {
                        p for p in self.game.battlefield.pieces.values()
                        if p.coord().x is active_x
                        and (p.type in pt.tank.value or p.type in pt.brick.value)
                        }

            # 1 if max range is reached or a game piece is within range
            clear_north = 1
            clear_east  = 1
            clear_south = 1
            clear_west  = 1

            # search north range for obstacles
            for ny in range(active_y - 1, active_y - max_range - 1, -1):
                if not self.map_properties[active_x][clip(ny, 0, self.max_y)] % 2:
                    clear_north = 0
                    break
            # search south range for obstacles
            for sy in range(active_y + 1, active_y + max_range + 1):
                if not self.map_properties[active_x][clip(sy, 0, self.max_y)] % 2:
                    clear_south = 0
                    break
            # search east range for obstacles
            for ex in range(active_x + 1, active_x + max_range + 1):
                if not self.map_properties[clip(ex, 0, self.max_x)][active_y] % 2:
                    clear_east = 0
                    break
            # search west range for obstacles
            for wx in range(active_x - 1, active_x - max_range - 1, -1):
                if not self.map_properties[clip(wx, 0, self.max_x)][active_y] % 2:
                    clear_west = 0
                    break

            # search north and south ranges for game pieces (tanks or bricks)
            for py in pieces_y:
                if py.coord().y in range(active_y - 1, ny - 1, -1):
                    if py.coord().y >= ny:
                        ny = py.coord().y
                        clear_north = 1
                elif py.coord().y in range(active_y + 1, sy + 1):
                    if py.coord().y <= sy:
                        sy = py.coord().y
                        clear_south = 1
            # search east and west ranges for game pieces (tanks or bricks)
            for px in pieces_x:
                if px.coord().x in range(active_x + 1, ex + 1):
                    if px.coord().x <= ex:
                        ex = px.coord().x
                        clear_east = 1
                elif px.coord().x in range(active_x - 1, wx - 1, -1):
                    if px.coord().x >= wx:
                        wx = px.coord().x
                        clear_west = 1

            # set positions
            self.sprites["north"].position = (center.x, (ny + 1.5 - clear_north) * self.tileheight)
            self.sprites["east"].position = ((ex - 0.5 + clear_east) * self.tilewidth, center.y)
            self.sprites["south"].position = (center.x, (sy - 0.5 + clear_south) * self.tileheight)
            self.sprites["west"].position = ((wx + 1.5 - clear_west) * self.tilewidth, center.y)

    def load_properties(self):
        return swapaxes(const.fourbase_properties, 0, 1).tolist()

    def draw(self):
        if self.game.state is gs.play:
            # draw range
            # self.game.window.draw(self.sprites["center"])
            self.game.window.draw(self.sprites["north"])
            self.game.window.draw(self.sprites["east"])
            self.game.window.draw(self.sprites["south"])
            self.game.window.draw(self.sprites["west"])
        elif self.game.state is gs.pan:
            # draw crosshair
            self.game.window.draw(self.sprites["pan"])
