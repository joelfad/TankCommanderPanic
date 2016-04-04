# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: inputhandler.py
# Author: Joel McFadden
# Created: March 26, 2016
# Modified: April 4, 2016

import sfml as sf
from gamestate import GameState as gs
from protocol import ActionType as action
from protocol import Cardinality as card

class InputHandler:

    def __init__(self, game):
        self.game = game
        self.mh = game.messagehandler

    def check_for_input(self):
        for event in self.game.window.events:
            if type(event) is sf.CloseEvent:
                self.quit()
            if type(event) is sf.KeyEvent and event.pressed:
                # quit if ctrl+Q is pressed
                if sf.Keyboard.is_key_pressed(sf.Keyboard.Q) and \
                   (sf.Keyboard.is_key_pressed(sf.Keyboard.R_CONTROL) or \
                   sf.Keyboard.is_key_pressed(sf.Keyboard.L_CONTROL)):
                    self.quit()
                # call mapped function
                if (self.game.state, event.code) in self.key_pressed_actions:
                    self.key_pressed_actions[(self.game.state, event.code)](self)
                    self.game.hud.update()

    # quit the game
    def quit(self):
        if self.game.state is not gs.wait:
            self.mh.send_message(action.quit.value,         # send quit message to server
                                 card.unspecified.value)
        self.mh.shutdown()                                  # close the connection
        self.game.window.close()                            # close the window

    # toggle pan
    def set_pan_on(self):
        self.game.prev = self.game.state
        self.game.state = gs.pan

    def set_pan_off(self):
        self.game.state = gs.prev
        self.game.center_view()

    # pan the map
    def pan_north(self):
        self.game.pan_view(0, -self.game.battlefield.tileheight)

    def pan_east(self):
        self.game.pan_view(self.game.battlefield.tilewidth, 0)

    def pan_south(self):
        self.game.pan_view(0, self.game.battlefield.tileheight)

    def pan_west(self):
        self.game.pan_view(-self.game.battlefield.tilewidth, 0)

    # switch tanks
    def next_tank(self):
        i = self.game.tanks.index(self.game.active_tank)
        self.game.active_tank = self.game.tanks[(i + 1) % len(self.game.tanks)]
        self.game.center_view()

    def set_tank_1(self):
        self.game.active_tank = self.game.tanks[0]
        if self.game.state is gs.pan:
            self.set_pan_off()
        else:
            self.game.center_view()

    def set_tank_2(self):
        if len(self.game.tanks) > 1:
            self.game.active_tank = self.game.tanks[1]
            if self.game.state is gs.pan:
                self.set_pan_off()
            else:
                self.game.center_view()

    def set_tank_3(self):
        if len(self.game.tanks) > 2:
            self.game.active_tank = self.game.tanks[2]
            if self.game.state is gs.pan:
                self.set_pan_off()
            else:
                self.game.center_view()

    def set_tank_4(self):
        if len(self.game.tanks) > 3:
            self.game.active_tank = self.game.tanks[3]
            if self.game.state is gs.pan:
                self.set_pan_off()
            else:
                self.game.center_view()

    # move requests
    def request_move_north(self):
        self.mh.send_message(action.attempt_move.value,
                             card.north.value,
                             self.game.active_tank.id)

    def request_move_east(self):
        self.mh.send_message(action.attempt_move.value,
                             card.east.value,
                             self.game.active_tank.id)

    def request_move_south(self):
        self.mh.send_message(action.attempt_move.value,
                             card.south.value,
                             self.game.active_tank.id)

    def request_move_west(self):
        self.mh.send_message(action.attempt_move.value,
                             card.west.value,
                             self.game.active_tank.id)

    # shoot requests
    def request_shoot_north(self):
        self.mh.send_message(action.attempt_shoot.value,
                             card.north.value,
                             self.game.active_tank.id)
        self.shoot_effect()

    def request_shoot_east(self):
        self.mh.send_message(action.attempt_shoot.value,
                             card.east.value,
                             self.game.active_tank.id)
        self.shoot_effect()

    def request_shoot_south(self):
        self.mh.send_message(action.attempt_shoot.value,
                             card.south.value,
                             self.game.active_tank.id)
        self.shoot_effect()

    def request_shoot_west(self):
        self.mh.send_message(action.attempt_shoot.value,
                             card.west.value,
                             self.game.active_tank.id)
        self.shoot_effect()

    # helper functions
    def shoot_effect(self):
        self.game.window.draw(self.game.active_tank, sf.RenderStates(sf.BLEND_ADD))
        self.game.window.display()  # TODO: Improve this effect and check ammo before displaying it

    # map game state and user input to functions
    key_pressed_actions = \
    {
        # toggle pan
        (gs.play, sf.Keyboard.TAB):     set_pan_on,
        (gs.won, sf.Keyboard.TAB):      set_pan_on,
        (gs.pan, sf.Keyboard.TAB):      set_pan_off,
        (gs.pan, sf.Keyboard.ESCAPE):   set_pan_off,

        # pan the map
        (gs.pan, sf.Keyboard.UP):       pan_north,
        (gs.pan, sf.Keyboard.RIGHT):    pan_east,
        (gs.pan, sf.Keyboard.DOWN):     pan_south,
        (gs.pan, sf.Keyboard.LEFT):     pan_west,
        (gs.lost, sf.Keyboard.UP):      pan_north,
        (gs.lost, sf.Keyboard.RIGHT):   pan_east,
        (gs.lost, sf.Keyboard.DOWN):    pan_south,
        (gs.lost, sf.Keyboard.LEFT):    pan_west,

        # switch tanks
        (gs.play, sf.Keyboard.SPACE):   next_tank,
        (gs.play, sf.Keyboard.NUM1):    set_tank_1,
        (gs.play, sf.Keyboard.NUM2):    set_tank_2,
        (gs.play, sf.Keyboard.NUM3):    set_tank_3,
        (gs.play, sf.Keyboard.NUM4):    set_tank_4,
        (gs.pan, sf.Keyboard.SPACE):    set_pan_off,
        (gs.pan, sf.Keyboard.NUM1):     set_tank_1,
        (gs.pan, sf.Keyboard.NUM2):     set_tank_2,
        (gs.pan, sf.Keyboard.NUM3):     set_tank_3,
        (gs.pan, sf.Keyboard.NUM4):     set_tank_4,
        (gs.won, sf.Keyboard.SPACE):    next_tank,
        (gs.won, sf.Keyboard.NUM1):     set_tank_1,
        (gs.won, sf.Keyboard.NUM2):     set_tank_2,
        (gs.won, sf.Keyboard.NUM3):     set_tank_3,
        (gs.won, sf.Keyboard.NUM4):     set_tank_4,

        # move requests
        (gs.play, sf.Keyboard.UP):      request_move_north,
        (gs.play, sf.Keyboard.RIGHT):   request_move_east,
        (gs.play, sf.Keyboard.DOWN):    request_move_south,
        (gs.play, sf.Keyboard.LEFT):    request_move_west,
        (gs.won, sf.Keyboard.UP):       request_move_north,
        (gs.won, sf.Keyboard.RIGHT):    request_move_east,
        (gs.won, sf.Keyboard.DOWN):     request_move_south,
        (gs.won, sf.Keyboard.LEFT):     request_move_west,

        # shoot requests
        (gs.play, sf.Keyboard.W):       request_shoot_north,
        (gs.play, sf.Keyboard.S):       request_shoot_east,
        (gs.play, sf.Keyboard.R):       request_shoot_south,
        (gs.play, sf.Keyboard.A):       request_shoot_west,
        (gs.won, sf.Keyboard.W):        request_shoot_north,
        (gs.won, sf.Keyboard.S):        request_shoot_east,
        (gs.won, sf.Keyboard.R):        request_shoot_south,
        (gs.won, sf.Keyboard.A):        request_shoot_west,
    }
