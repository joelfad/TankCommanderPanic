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
        self.update_stats()
        self.update_range()

    def update_stats(self): # TODO: Remove magic numbers in this function
        # translucent overlay
        self.stats_box = sf.RectangleShape((960, 32))
        self.stats_box.position = self.game.window.map_pixel_to_coords((0, 672))
        self.stats_box.fill_color = sf.Color(0, 0, 0, 160)

        self.stats = []

        # tank health
        position_x = 0
        tank_colors = [self.tank_data[t.type][2] for t in self.game.tanks]
        for i, tank in enumerate(self.game.tanks):
            t = sf.Text(" {}:{} ".format(self.tank_data[tank.type][0], tank.value))
            t.font = self.game.texturehandler.font
            t.character_size = 8
            t.position = self.game.window.map_pixel_to_coords((position_x, 680))
            if tank is self.game.active_tank:
                t.color = self.tank_data[tank.type][2]
            position_x += t.local_bounds.width * 2
            self.stats.append(t)

        # ammo
        a = sf.Text("*{} ".format(self.game.ammo))
        a.font = self.game.texturehandler.font
        a.character_size = 8
        a.position = self.game.window.map_pixel_to_coords((960 - a.local_bounds.width * 2, 680))
        self.stats.append(a)

    def update_range(self):
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

            # search north range for obstacles
            for ny in range(active_y - 1, active_y - max_range - 1, -1):
                if not self.map_properties[active_x][clip(ny, 0, self.max_y)] % 2:
                    break
            # search south range for obstacles
            for sy in range(active_y + 1, active_y + max_range + 1):
                if not self.map_properties[active_x][clip(sy, 0, self.max_y)] % 2:
                    break
            # search east range for obstacles
            for ex in range(active_x + 1, active_x + max_range + 1):
                if not self.map_properties[clip(ex, 0, self.max_x)][active_y] % 2:
                    break
            # search west range for obstacles
            for wx in range(active_x - 1, active_x - max_range - 1, -1):
                if not self.map_properties[clip(wx, 0, self.max_x)][active_y] % 2:
                    break

            # search north and south ranges for game pieces (tanks or bricks)
            for py in pieces_y:
                if py.coord().y in range(active_y - 1, ny, -1):
                    if py.coord().y > ny:
                        ny = py.coord().y
                elif py.coord().y in range(active_y + 1, sy):
                    if py.coord().y < sy:
                        sy = py.coord().y
            # search east and west ranges for game pieces (tanks or bricks)
            for px in pieces_x:
                if px.coord().x in range(active_x + 1, ex):
                    if px.coord().x < ex:
                        ex = px.coord().x
                elif px.coord().x in range(active_x - 1, wx, -1):
                    if px.coord().x > wx:
                        wx = px.coord().x

            # set positions
            self.sprites["center"].position = center
            self.sprites["north"].position = (center.x, (ny + 0.5) * self.tileheight)
            self.sprites["east"].position = ((ex + 0.5) * self.tilewidth, center.y)
            self.sprites["south"].position = (center.x, (sy + 0.5) * self.tileheight)
            self.sprites["west"].position = ((wx + 0.5) * self.tilewidth, center.y)

    def load_properties(self):
        return swapaxes(const.fourbase_properties, 0, 1).tolist()

    def draw(self):
        self.draw_stats()
        self.draw_range()

    def draw_stats(self):
        self.game.window.draw(self.stats_box)
        for s in self.stats:
            self.game.window.draw(s)

    def draw_range(self):
        # TODO: Use sprites as an inversion mask for better contrast
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
