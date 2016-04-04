# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: gamestate.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 4, 2016

from enum import Enum

class GameState(Enum):
    wait    = 0 # waiting for initial game state
    play    = 1 # playing the game (controlling tanks)
    pan     = 2 # panning the map (active player)
    lost    = 3 # game over (player lost)
    won     = 4 # game over (player won)
