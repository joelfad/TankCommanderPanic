# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: inputhandler.py
# Author: Joel McFadden
# Created: March 26, 2016
# Modified: March 31, 2016

import sfml as sf
from gamestate import GameState as gs

class InputHandler:

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
        print("Pan UP")

    def pan_east(self):
        print("Pan RIGHT")

    def pan_south(self):
        print("Pan DOWN")

    def pan_west(self):
        print("Pan LEFT")

    # switch tanks
    def next_tank(self):
        i = self.game.tanks.index(self.game.active_tank)
        self.game.active_tank = self.game.tanks[(i + 1) % len(self.game.tanks)]

    def set_tank_1(self):
        self.game.active_tank = self.game.tanks[0]

    def set_tank_2(self):
        if len(self.game.tanks) > 1:
            self.game.active_tank = self.game.tanks[1]

    def set_tank_3(self):
        if len(self.game.tanks) > 2:
            self.game.active_tank = self.game.tanks[2]

    def set_tank_4(self):
        if len(self.game.tanks) > 3:
            self.game.active_tank = self.game.tanks[3]

    # move active tank
    def move_north(self, units):
        self.game.active_tank.move(0, -units).rotation = 0

    def move_east(self, units):
        self.game.active_tank.move(units, 0).rotation = 90

    def move_south(self, units):
        self.game.active_tank.move(0, units).rotation = 180

    def move_west(self, units):
        self.game.active_tank.move(-units, 0).rotation = 270

    # move requests
    def request_move_north(self):
        self.move_north(1)

    def request_move_east(self):
        self.move_east(1)

    def request_move_south(self):
        self.move_south(1)

    def request_move_west(self):
        self.move_west(1)

    # shoot requests
    def request_shoot_north(self):
        print("Shoot UP")
        self.game.active_tank.rotation = 0

    def request_shoot_east(self):
        print("Shoot RIGHT")
        self.game.active_tank.rotation = 90

    def request_shoot_south(self):
        print("Shoot DOWN")
        self.game.active_tank.rotation = 180

    def request_shoot_west(self):
        print("Shoot LEFT")
        self.game.active_tank.rotation = 270

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
        (gs.play, sf.Keyboard.W):       request_shoot_north,
        (gs.play, sf.Keyboard.S):       request_shoot_east,
        (gs.play, sf.Keyboard.R):       request_shoot_south,
        (gs.play, sf.Keyboard.A):       request_shoot_west,
    }
