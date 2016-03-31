# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: game.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 30, 2016

import sfml as sf
from battlefield import *
from texturehandler import *
from inputhandler import *
from gamestate import GameState as gs
from const import ammo # TODO: Remove after Event Messages can be received
from random import randint # TODO: Remove after Game State Message can be received
from hud import HUD

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class Game:

    def __init__(self):
        self.state = gs.wait
        self.window = self.create_window()
        self.battlefield = BattleField(self)
        self.hud = HUD(self)
        self.inputhandler = InputHandler(self)
        # self.messagehandler = MessageHandler(self)

    def process_events(self):
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
        v = sf.View(sf.Rect((0, 0), (WINDOW_WIDTH, WINDOW_HEIGHT)))
        w.view = v

        # limit the framerate to 60 fps
        w.framerate_limit = 60

        return w

    def load_texture(self, texture_data):
        self.texturehandler = TextureHandler(*texture_data)
        return self.texturehandler.texture

    def get_texture_rect(self, tile_id):
        return self.texturehandler.get_rect(tile_id)

    # set the state of the game
    def set_state(self):
        self.player_id = randint(0, 32767) # TODO: Receive this value from Game State Message
        self.ammo = const.ammo # TODO: Receive this value from Event Message (Update Ammo)
        self.tanks = const.tank_piece_id # TODO: Receive this value from Game State Message
        self.active_tank = self.tanks[0]
        self.state = gs.play
