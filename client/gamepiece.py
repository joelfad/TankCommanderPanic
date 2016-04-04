# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: gamepiece.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 31, 2016

from sfml import Sprite
from enum import Enum
from const import sprite_map

class GamePiece(Sprite):

    def __init__(self, id, position, type, value, texturehandler):
        super(self.__class__, self).__init__(texturehandler.texture)
        self.id = id
        self.type = type
        self.position = position
        self.value = value

        # set origin to center of piece for rotations
        self.origin = self.set_texture_rect(texturehandler)
        self.position += self.origin

    def set_texture_rect(self, texturehandler):
        sprite_id = sprite_map[self.type]
        if not sprite_id:
            sprite_id = self.type
        self.texture_rectangle = texturehandler.get_rect(sprite_id)
        return (self.texture_rectangle.width / 2, self.texture_rectangle.height / 2) # center

    def move(self, x, y):
        super(self.__class__, self).move((x * self.texture_rectangle.width,
                                          y * self.texture_rectangle.height))
        return self

# TODO: Use this to set the sprite based on GamePiece value
class PieceType(Enum):
    brick = {n for n in range(2, 8)}
    health = {8}
    ammo = {9}
    decoration = {10}
    tank = {n for n in range(16, 32)}
