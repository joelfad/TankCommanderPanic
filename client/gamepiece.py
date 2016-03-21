# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: gamepiece.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 20, 2016

from sfml import Sprite

class GamePiece(Sprite):
    # id : int
    # type : byte
    # value : int
    # sprite_map : dict

    def __init__(self):
        Sprite.__init__()
        # initialize here

    def draw(self):
        # draw game piece
