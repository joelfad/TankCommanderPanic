# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: const.py
# Author: Joel McFadden
# Created: March 29, 2016
# Modified: April 2, 2016

import sfml as sf

#############
# Constants #
#############

# piece_type mapped to tile_id
sprite_map = \
{
    2:  384,    # brick
    3:  384,    # brick
    4:  384,    # brick
    5:  384,    # brick
    6:  384,    # brick
    7:  384,    # brick

    8:  480,    # health

    9:  478,    # ammo

    10: 0,      # decoration

    16: 484,    # red commander
    17: 485,    # red interceptor
    18: 486,    # red eliminator
    19: 487,    # red negotiator

    20: 505,    # blue commander
    21: 506,    # blue interceptor
    22: 507,    # blue eliminator
    23: 508,    # blue negotiator

    24: 526,    # yellow commander
    25: 527,    # yellow interceptor
    26: 528,    # yellow eliminator
    27: 529,    # yellow negotiator

    28: 547,    # green commander
    29: 548,    # green interceptor
    30: 549,    # green eliminator
    31: 550,    # green negotiator
}

COMMANDER_RANGE     = 6
INTERCEPTOR_RANGE   = 6
ELIMINATOR_RANGE    = 3
NEGOTIATOR_RANGE    = 12

# piece_type mapped to tank data
tank_data = \
{
    16: ("Commander", COMMANDER_RANGE, sf.Color.RED),
    20: ("Commander", COMMANDER_RANGE, sf.Color.BLUE),
    24: ("Commander", COMMANDER_RANGE, sf.Color.YELLOW),
    28: ("Commander", COMMANDER_RANGE, sf.Color.GREEN),

    17: ("Interceptor", INTERCEPTOR_RANGE, sf.Color.RED),
    21: ("Interceptor", INTERCEPTOR_RANGE, sf.Color.BLUE),
    25: ("Interceptor", INTERCEPTOR_RANGE, sf.Color.YELLOW),
    29: ("Interceptor", INTERCEPTOR_RANGE, sf.Color.GREEN),

    18: ("Eliminator", ELIMINATOR_RANGE, sf.Color.RED),
    22: ("Eliminator", ELIMINATOR_RANGE, sf.Color.BLUE),
    26: ("Eliminator", ELIMINATOR_RANGE, sf.Color.YELLOW),
    30: ("Eliminator", ELIMINATOR_RANGE, sf.Color.GREEN),

    19: ("Negotiator", NEGOTIATOR_RANGE, sf.Color.RED),
    23: ("Negotiator", NEGOTIATOR_RANGE, sf.Color.BLUE),
    27: ("Negotiator", NEGOTIATOR_RANGE, sf.Color.YELLOW),
    31: ("Negotiator", NEGOTIATOR_RANGE, sf.Color.GREEN),
}

hud_sprites = \
{
    "center":   488,
    "north":    510,
    "east":     531,
    "south":    530,
    "west":     509,
    "pan":      489,
}

#############
# Mock Data #
#############

# received from server
id_ = 2              # map id
version = 1         # map version
ammo = 500          # ammo count
tank_piece_id = [1000, 2000, 3000] # ids of owned tanks

# determined from load_map_data
name = "Fourbase"   # map name
piece_layer = 3     # layer (counting from 0) that the game pieces will be drawn on top of
image_source = "palette.png"    # name of texture file for map
width = 32          # number of horizontal tiles
height = 32         # number of vertical tiles
tilewidth = 32      # pixels wide per tile graphic
tileheight = 32     # pixels high per tile graphic
tilecount = 567     # total number of tiles in texture
columns = 21        # columns in texture

# mock properties
tank_range = 5

# mock tanks
red_commander = (1000, 1, 1, 16, 20)
red_interceptor = (2000, 3, 2, 17, 20)
red_eliminator = (3000, 2, 3, 18, 20)

blue_commander = (1100, 30, 1, 20, 20)
blue_interceptor = (2200, 29, 3, 21, 20)
blue_eliminator = (3300, 28, 2, 22, 20)

yellow_commander = (1110, 1, 30, 24, 20)
yellow_interceptor = (2220, 2, 28, 25, 20)
yellow_eliminator = (3330, 3, 29, 26, 20)

green_commander = (1111, 30, 30, 28, 20)
green_interceptor = (2222, 28, 29, 29, 20)
green_eliminator = (3333, 29, 28, 30, 20)

fourbase_tanks = \
{
    red_commander,
    red_interceptor,
    red_eliminator,
    blue_commander,
    blue_interceptor,
    blue_eliminator,
    yellow_commander,
    yellow_interceptor,
    yellow_eliminator,
    green_commander,
    green_interceptor,
    green_eliminator
}

# mock map data
fourbase_tile_ids = \
[
    [   # layer: back
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [359,359,359,359,359,359,359,359,359,359,359,359,359,359,359,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,329,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    ],
    [   # layer: base
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,201,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68],
        [221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,222,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329],
        [317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,318,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329,329]
    ],
    [   # layer: water
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,61,62,62,62,62,62,62,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,82,83,83,83,83,126,83,84,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,82,124,83,20,104,104,104,105,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,82,83,125,84,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,103,104,104,105,0,0,0,0,0,0,0,0,55,56,57,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,77,78,0,0,0,55,56,56,56,57,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,98,99,0,0,0,76,77,77,77,78,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,77,115,77,78,0,0],
        [0,0,0,0,0,0,61,62,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,98,15,77,78,0,0],
        [0,0,0,0,0,0,82,125,84,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,77,78,0,0],
        [0,0,0,0,0,0,103,104,105,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,77,78,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,77,78,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,98,99,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,257,341,258,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,321,83,319,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,321,124,319,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,304,305,306,0,0,0,0,0,0],
        [0,0,321,83,319,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,325,369,327,0,0,0,0,0,0],
        [0,0,321,83,340,341,258,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,346,347,348,0,0,0,0,0,0],
        [0,0,321,83,83,126,319,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,321,125,83,323,319,0,0,0,257,341,258,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,278,299,299,299,279,0,0,0,321,124,319,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,278,299,279,0,0,0,0,0,0,0,0,304,305,305,306,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,325,326,369,327,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,304,305,305,305,285,369,326,327,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,325,326,367,326,368,326,368,327,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,346,347,347,347,347,347,347,348,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    ],
    [   # layer: rock
        [398,419,420,398,398,419,399,419,419,420,399,397,399,399,420,420,440,441,441,440,440,440,440,441,440,440,441,440,440,441,440,440],
        [398,0,0,0,0,0,0,427,0,0,0,0,0,0,0,0,0,0,0,0,0,441,0,0,0,0,0,0,0,0,0,440],
        [419,0,0,0,420,0,0,0,0,0,0,0,0,0,0,0,0,0,440,0,0,440,0,0,440,0,0,440,0,0,0,441],
        [420,0,0,0,398,0,0,0,0,0,0,0,0,0,0,0,0,0,441,0,0,0,0,0,441,0,0,441,0,0,0,440],
        [397,0,420,399,419,0,0,0,0,0,0,0,0,0,0,0,0,0,440,441,440,440,441,440,440,0,0,440,441,440,0,441],
        [418,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,441,0,0,0,0,0,0,0,441],
        [420,0,0,0,0,0,0,0,0,0,0,0,0,0,0,419,0,0,0,0,0,0,0,440,0,0,0,0,0,0,0,441],
        [398,0,419,399,420,0,0,0,0,0,0,0,420,0,0,420,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,440],
        [419,0,0,0,398,399,420,0,0,0,0,0,398,0,0,398,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,440],
        [420,0,0,0,419,0,0,0,0,0,0,0,419,0,0,419,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,441],
        [420,399,420,0,420,0,0,0,0,0,0,0,420,0,0,420,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,441],
        [398,0,0,0,398,0,0,0,0,0,0,420,419,0,0,419,0,0,0,0,441,0,0,0,0,0,0,0,0,0,0,440],
        [419,0,0,0,420,0,0,0,0,0,0,0,0,0,0,398,0,0,0,0,440,441,440,441,440,0,0,0,0,0,0,440],
        [420,0,420,399,419,0,0,0,0,0,0,0,0,0,0,419,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,441],
        [398,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,440],
        [420,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,440,441,440,441,440,440,441,440,0,0,0,0,0,440],
        [462,0,0,0,0,0,483,460,483,439,439,483,439,483,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,420],
        [439,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,397],
        [462,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,420,0,0,0,0,0,0,0,0,0,0,419,418,419,0,420],
        [483,0,0,0,0,0,0,483,460,483,439,483,0,0,0,0,419,0,0,0,0,0,0,0,0,0,0,418,0,0,0,418],
        [460,0,0,0,0,0,0,0,0,0,0,462,0,0,0,0,420,0,0,419,420,0,0,0,0,0,0,419,0,0,0,419],
        [439,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,397,0,0,399,0,0,0,0,0,0,0,420,0,420,397,420],
        [462,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,418,0,0,420,0,0,0,0,0,0,0,419,0,0,0,419],
        [483,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,419,0,0,398,0,0,0,0,0,419,418,420,0,0,0,420],
        [462,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,420,0,0,419,0,0,0,0,0,0,0,420,418,419,0,397],
        [483,0,0,0,0,0,0,0,483,0,0,0,0,0,0,0,397,0,0,0,0,0,0,0,0,0,0,0,0,0,0,418],
        [460,0,0,0,0,0,0,0,460,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,419],
        [483,0,483,439,462,0,0,483,439,483,462,483,460,483,0,0,0,0,0,0,0,0,0,0,0,0,0,419,397,420,0,420],
        [462,0,0,0,460,0,0,460,0,0,0,0,0,460,0,0,0,0,0,0,0,0,0,0,0,0,0,399,0,0,0,397],
        [439,0,0,0,483,0,0,462,0,0,483,0,0,462,0,0,0,0,0,0,0,0,0,0,0,0,0,420,0,0,0,418],
        [462,0,0,0,0,0,0,0,0,0,439,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,419],
        [460,462,483,439,483,462,483,460,483,439,483,462,483,460,439,462,419,420,397,398,399,420,419,420,419,397,398,399,419,420,419,420]
    ],
    # [   # layer: tanks
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,484,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,485,0],
    #     [0,0,0,505,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,527,0,0,0],
    #     [0,0,526,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,548,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,484,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,506,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,528,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,550,0,0,505,527,549,487,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,526,548,486,508,0,0,547,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,485,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,507,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,529,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    #     [0,0,507,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,508,0,0],
    #     [0,0,0,549,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,529,0,0,0],
    #     [0,486,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,487,0],
    #     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    # ],
    [   # layer: foliage
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,175,176,176,177,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,196,238,239,198,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,217,218,218,219,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,133,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,127,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,154,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,169,170,170,171,0,0,0,0,169,170,171,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,175,176,177,0,0,0,0,190,233,234,192,0,0,0,0,190,232,192,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,196,240,198,0,0,0,0,211,212,212,213,0,0,0,0,190,233,192,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,196,238,198,0,0,0,0,0,0,0,0,0,0,0,0,211,212,213,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,217,218,219,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,493,494,495,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,172,173,174,0,0,0,0,0,0,0,0,0,0,0,0,514,532,516,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,193,234,195,0,0,0,0,172,173,173,174,0,0,0,0,514,533,516,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,193,233,195,0,0,0,0,193,234,234,195,0,0,0,0,535,536,537,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,214,215,216,0,0,0,0,214,215,215,216,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,127,148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,490,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,493,494,494,495,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,514,533,534,516,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,535,536,536,537,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    ]
]

fourbase_properties = \
[
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0],
    [0,3,3,3,0,3,3,1,1,1,1,1,1,1,1,3,3,3,0,3,3,0,3,3,0,3,3,0,3,3,3,0],
    [0,3,3,3,0,3,3,1,1,1,1,1,1,1,1,3,3,3,0,3,3,3,3,3,0,3,3,0,3,3,3,0],
    [0,3,0,0,0,3,3,1,1,1,0,0,0,0,1,3,3,3,0,0,0,0,0,0,0,3,3,0,0,0,3,0],
    [0,3,3,3,3,3,3,1,1,1,0,2,2,2,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0],
    [0,3,3,3,3,3,3,1,1,1,0,2,2,2,3,0,3,3,3,1,1,1,3,0,3,3,3,3,3,3,3,0],
    [0,3,0,0,0,3,3,2,3,3,3,3,0,3,3,0,3,3,3,1,1,1,3,2,2,1,1,1,1,1,3,0],
    [0,3,3,3,0,0,0,2,3,3,3,3,0,3,3,0,3,3,3,1,1,1,3,3,3,1,1,1,1,1,3,0],
    [0,3,3,3,0,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3,3,3,1,1,1,1,1,3,0],
    [0,0,0,3,0,3,1,1,1,3,3,3,0,3,3,0,3,2,2,2,2,3,3,3,3,0,0,0,1,1,3,0],
    [0,3,3,3,0,3,1,1,1,3,2,0,0,3,3,0,3,2,2,2,0,3,3,3,3,2,2,0,1,1,3,0],
    [0,3,3,3,0,3,1,1,1,3,2,2,2,3,3,0,3,2,2,2,0,0,0,0,0,2,2,0,1,1,3,0],
    [0,3,0,0,0,3,3,3,3,3,2,2,2,3,3,0,3,3,3,3,3,3,3,3,3,2,2,0,1,1,3,0],
    [0,3,3,3,3,3,3,3,3,3,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,3,0],
    [0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,3,3,3,3,3,0],
    [0,3,3,3,3,3,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0],
    [0,3,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,3,3,3,3,3,3,3,3,3,0],
    [0,3,1,1,0,2,2,3,3,3,3,3,3,3,3,3,0,3,3,2,2,2,3,3,3,3,3,0,0,0,3,0],
    [0,3,1,1,0,2,2,0,0,0,0,0,2,2,2,3,0,3,3,2,2,2,3,1,1,1,3,0,3,3,3,0],
    [0,3,1,1,0,2,2,3,3,3,3,0,2,2,2,3,0,3,3,0,0,2,3,1,1,1,3,0,3,3,3,0],
    [0,3,1,1,0,0,0,3,3,3,3,2,2,2,2,3,0,3,3,0,3,3,3,1,1,1,3,0,3,0,0,0],
    [0,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3,0,3,3,3,0],
    [0,3,1,1,1,1,1,3,3,3,1,1,1,3,3,3,0,3,3,0,3,3,3,3,2,0,0,0,3,3,3,0],
    [0,3,1,1,1,1,1,2,2,3,1,1,1,3,3,3,0,3,3,0,3,3,3,3,2,3,3,0,0,0,3,0],
    [0,3,3,3,3,3,3,3,0,3,1,1,1,3,3,3,0,3,2,2,2,0,1,1,1,3,3,3,3,3,3,0],
    [0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,2,2,2,0,1,1,1,3,3,3,3,3,3,0],
    [0,3,0,0,0,3,3,0,0,0,0,0,0,0,3,3,3,1,0,0,0,0,1,1,1,3,3,0,0,0,3,0],
    [0,3,3,3,0,3,3,0,3,3,3,3,3,0,3,3,3,1,1,1,1,1,1,1,1,3,3,0,3,3,3,0],
    [0,3,3,3,0,3,3,0,3,3,0,3,3,0,3,3,3,1,1,1,1,1,1,1,1,3,3,0,3,3,3,0],
    [0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
]
