# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: inputhandler.py
# Author: Joel McFadden
# Created: March 26, 2016
# Modified: March 29, 2016

import sfml as sf

class InputHandler:
    # key_actions : {KeyEvent : function}

    def __init__(self, game):
        self.game = game

    def check_for_input(self):
        for event in self.game.window.events:
            if type(event) is sf.CloseEvent:
                self.game.window.close()
            if type(event) is sf.KeyEvent:
                # lookup event.code in dictionary
                pass

    def request_move_left(self):
        # self.game.active_tank
        pass
