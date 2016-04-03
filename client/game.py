# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: game.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 2, 2016

import sfml as sf
from numpy import clip
from battlefield import *
from texturehandler import *
from inputhandler import *
from gamestate import GameState as gs
from const import ammo # TODO: Remove after Event Messages can be received
from random import randint # TODO: Remove after Game State Message can be received
from hud import HUD

# display constants
TILE_WIDTH      = 32
TILE_HEIGHT     = 32
TILES_X         = 15
TILES_Y         = 11
RATIO           = 2
HUD_HEIGHT      = TILE_HEIGHT * RATIO
VIEW_WIDTH      = TILE_WIDTH  * TILES_X
VIEW_HEIGHT     = TILE_HEIGHT * TILES_Y
WINDOW_WIDTH    = VIEW_WIDTH  * RATIO
WINDOW_HEIGHT   = VIEW_HEIGHT * RATIO + HUD_HEIGHT

class Game:

    def __init__(self):
        self.state = gs.wait
        self.window = self.create_window()
        self.battlefield = BattleField(self)
        self.inputhandler = InputHandler(self)
        # self.messagehandler = MessageHandler(self)

    def process_events(self):
        # handle messages first (in case the last tank is destroyed)
        self.inputhandler.check_for_input()

    def render(self):
        self.window.clear()
        self.battlefield.draw()
        self.hud.draw()
        self.window.display()

    def run(self):
        while self.window.is_open:
            self.process_events()
            # self.update()
            self.render()

    def create_window(self):
        # create a new window
        size, bpp = sf.VideoMode.get_desktop_mode()    # get bits per pixel
        w = sf.RenderWindow(sf.VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, bpp), "Tank Commander Panic")

        # set the window view
        v = sf.View(sf.Rect((0, 0), (VIEW_WIDTH, VIEW_HEIGHT)))
        v.viewport = (0.0, 0.0, 1.0, (WINDOW_HEIGHT - HUD_HEIGHT) / WINDOW_HEIGHT)
        w.view = v

        # limit the framerate to 60 fps
        w.framerate_limit = 60

        return w

    def load_texture(self, texture_data):
        self.texturehandler = TextureHandler(*texture_data)
        return self.texturehandler.texture

    def get_texture_rect(self, tile_id):
        return self.texturehandler.get_rect(tile_id)

    # center view on active tank
    def center_view(self):
        self.set_view(*self.active_tank.position)

    # move view by offset
    def pan_view(self, delta_x, delta_y):
        self.set_view(self.window.view.center.x + delta_x, self.window.view.center.y + delta_y)

    def set_view(self, x, y):
        # calculate center_x
        center_x = clip(x, 0.5 * VIEW_WIDTH, -0.5 * VIEW_WIDTH + self.battlefield.mapwidth)

        # calculate center_y
        center_y = clip(y, 0.5 * VIEW_HEIGHT, -0.5 * VIEW_HEIGHT + self.battlefield.mapwidth)

        # update view
        self.window.view.center = (center_x, center_y)

    # set the state of the game
    def set_state(self):
        self.player_id = randint(0, 32767) # TODO: Receive this value from Game State Message
        self.ammo = const.ammo # TODO: Receive this value from Event Message (Update Ammo)
        self.tanks = [self.battlefield.get_piece(id_) for id_ in const.tank_piece_id] # TODO: Receive this value from Game State Message
        self.active_tank = self.tanks[0]
        self.hud = HUD(self)
        self.state = gs.play
