# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: game.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 4, 2016

import sfml as sf
from numpy import clip
from battlefield import *
from texturehandler import *
from fonthandler import *
from messagehandler import *
from inputhandler import *
from gamestate import GameState as gs
from hud import HUD

# display constants
TILE_WIDTH      = 32
TILE_HEIGHT     = 32
TILES_X         = 15
TILES_Y         = 11
RATIO           = 2
# HUD_HEIGHT      = TILE_HEIGHT * RATIO
HUD_HEIGHT      = 0 # TODO: Draw the HUD in a separate area
VIEW_WIDTH      = TILE_WIDTH  * TILES_X
VIEW_HEIGHT     = TILE_HEIGHT * TILES_Y
WINDOW_WIDTH    = VIEW_WIDTH  * RATIO
WINDOW_HEIGHT   = VIEW_HEIGHT * RATIO + HUD_HEIGHT

class Game:

    def __init__(self, server_addr):
        self.state = gs.wait
        self.window = self.create_window()
        self.fonthandler = FontHandler()
        self.messagehandler = MessageHandler(self, server_addr)
        self.inputhandler = InputHandler(self)

    def process_events(self):
        self.messagehandler.check_for_messages()
        self.inputhandler.check_for_input()

    def render(self):
        self.window.clear()
        if self.state is not gs.wait:
            self.battlefield.draw()
            self.hud.draw()
        else:
            self.draw_wait()
        self.window.display()

    def run(self):
        while self.window.is_open:
            self.process_events()
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

    def draw_wait(self):
        wait = sf.Text(" Waiting for server to start game...")
        wait.font = self.fonthandler.font
        wait.character_size = 8
        wait.position = self.window.map_pixel_to_coords((0, 680))
        self.window.draw(wait)

    # set the state of the game
    def set_state(self, map_id, map_version, player_id, tank_piece_ids):
        self.map_id = map_id
        self.map_version = map_version
        self.player_id = player_id
        self.tanks = tank_piece_ids

        # create battlefield
        self.battlefield = BattleField(self, map_id, map_version)

    def start(self):
        # set up tanks
        self.tanks = [self.battlefield.get_piece(id_) for id_ in self.tanks]
        self.active_tank = self.tanks[0]

        self.state = gs.play
        self.prev = gs.play

        # create hud
        self.hud = HUD(self, self.map_id, self.map_version)
