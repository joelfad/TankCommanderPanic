# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: protocol.py
# Author: Joel McFadden
# Created: April 3, 2016
# Modified: April 3, 2016

from enum import Enum

class ActionType(Enum):
    no_action       = 0
    attempt_move    = 1
    attempt_shoot   = 2
    quit            = 3

class Cardinality(Enum):
    unspecified     = 0
    north           = 1
    east            = 2
    south           = 3
    west            = 4

class PieceType(Enum):
    brick = {n for n in range(2, 8)}
    health = {8}
    ammo = {9}
    decoration = {10}
    tank = {n for n in range(16, 32)}

class EventType(Enum):
    update_ammo     = 32
    update_heath    = 33
    destroy_piece   = 34
    move_piece      = 35
    game_over       = 36
