# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: const.py
# Author: Joel McFadden
# Created: March 29, 2016
# Modified: April 4, 2016

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
