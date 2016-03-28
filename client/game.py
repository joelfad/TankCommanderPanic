# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: game.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 20, 2016

import sfml as sf
from battlefield import *

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class Game:
    # state : Enum('playing', 'observing')
    # window : Window
    # hud : HUD
    # battlefield : BattleField
    # tanks : GamePiece[]
    # active_tank : byte
    # ammo : int
    # player_name : str
    # message_handler : MessageHandler
    # message_actions : (function)
    # key_actions : {KeyEvent : function}

    def __init__(self):
        self.window = self.create_window()
        self.battlefield = BattleField(self)
        self.window.clear(sf.Color.BLUE)
        self.window.display()
        self.battlefield.draw()
        self.window.display()
        input("Press enter to quit...")

    def process_events(self):
        # process events here
        pass

    def render(self):
        # render the game
        pass

    def run(self):
        # run the game
        pass

    def create_window(self):
        w = sf.RenderWindow(sf.VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Commander Panic")
        w.view.viewport = sf.Rect((0,0), (WINDOW_WIDTH, WINDOW_HEIGHT))
        return w
