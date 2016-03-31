# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: hud.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 30, 2016

class HUD:
    # texture : Texture

    def __init__(self, game):
        self.game = game
        self.texture = game.texturehandler.texture

    def load_texture(self):
        # load texture from file
        pass

    def draw(self):
        # draw the HUD
        pass
