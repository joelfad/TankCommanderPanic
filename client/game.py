# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: game.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 29, 2016

import sfml as sf
from battlefield import *
from texturehandler import *
from inputhandler import *

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class Game:
    # state : Enum('playing', 'observing')
    # hud : HUD
    # tanks : GamePiece[]
    # active_tank : byte
    # ammo : int
    # player_name : str

    def __init__(self):
        self.window = self.create_window()
        self.battlefield = BattleField(self)
        self.inputhandler = InputHandler(self)
        # self.messagehandler = MessageHandler(self)

    def process_events(self):
        self.inputhandler.check_for_input()

    def render(self):
        self.window.clear()
        self.battlefield.draw()
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
