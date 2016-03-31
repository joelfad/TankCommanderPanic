# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: inputhandler.py
# Author: Joel McFadden
# Created: March 26, 2016
# Modified: March 30, 2016

import sfml as sf
from gamestate import GameState as gs

class InputHandler:
    up_count    = 0 # TODO: Remove these lines after key_event functions are implemented
    right_count = 0 #
    down_count  = 0 #
    left_count  = 0 #

    def __init__(self, game):
        self.game = game

    def check_for_input(self):
        for event in self.game.window.events:
            if type(event) is sf.CloseEvent:
                self.game.window.close()
            if type(event) is sf.KeyEvent and event.pressed:
                # call mapped function
                if (self.game.state, event.code) in self.key_actions:
                    self.key_actions[(self.game.state, event.code)](self)


    # toggle pan
    def set_pan_on(self):
        self.game.state = gs.pan
        print("-- Pan ON --")

    def set_pan_off(self):
        self.game.state = gs.play
        print("-- Pan OFF --")

    # pan the map
    def pan_north(self):
        pass

    def pan_east(self):
        pass

    def pan_south(self):
        pass

    def pan_west(self):
        pass

    # switch tanks
    def next_tank(self):
        pass

    def set_tank_1(self):
        pass

    def set_tank_2(self):
        pass

    def set_tank_3(self):
        pass

    def set_tank_4(self):
        pass

    # move requests
    def request_move_north(self):
        # self.game.active_tank
        self.up_count += 1
        print("{} UP pressed".format(self.up_count))

    def request_move_east(self):
        self.right_count += 1
        print("{} RIGHT pressed".format(self.right_count))

    def request_move_south(self):
        self.down_count += 1
        print("{} DOWN pressed".format(self.down_count))

    def request_move_west(self):
        self.left_count += 1
        print("{} LEFT pressed".format(self.left_count))

    # shoot requests
    def request_shoot_north(self):
        pass

    def request_shoot_east(self):
        pass

    def request_shoot_south(self):
        pass

    def request_shoot_west(self):
        pass

    # map game state and user input to functions
    key_actions = \
    {
        # toggle pan
        (gs.play, sf.Keyboard.TAB):     set_pan_on,
        (gs.pan, sf.Keyboard.TAB):      set_pan_off,

        # pan the map
        (gs.pan, sf.Keyboard.UP):       pan_north,
        (gs.pan, sf.Keyboard.RIGHT):    pan_east,
        (gs.pan, sf.Keyboard.DOWN):     pan_south,
        (gs.pan, sf.Keyboard.LEFT):     pan_west,
        (gs.obs, sf.Keyboard.UP):       pan_north,
        (gs.obs, sf.Keyboard.RIGHT):    pan_east,
        (gs.obs, sf.Keyboard.DOWN):     pan_south,
        (gs.obs, sf.Keyboard.LEFT):     pan_west,

        # switch tanks
        (gs.play, sf.Keyboard.SPACE):   next_tank,
        (gs.play, sf.Keyboard.NUM1):    set_tank_1,
        (gs.play, sf.Keyboard.NUM2):    set_tank_2,
        (gs.play, sf.Keyboard.NUM3):    set_tank_3,
        (gs.play, sf.Keyboard.NUM4):    set_tank_4,

        # move requests
        (gs.play, sf.Keyboard.UP):      request_move_north,
        (gs.play, sf.Keyboard.RIGHT):   request_move_east,
        (gs.play, sf.Keyboard.DOWN):    request_move_south,
        (gs.play, sf.Keyboard.LEFT):    request_move_west,

        # shoot requests
        (gs.play, sf.Keyboard.W):       request_move_north,
        (gs.play, sf.Keyboard.S):       request_move_east,
        (gs.play, sf.Keyboard.R):       request_move_south,
        (gs.play, sf.Keyboard.A):       request_move_west,
    }
