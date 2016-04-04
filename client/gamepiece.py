# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: gamepiece.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 3, 2016

from sfml import Sprite, Vector2
from const import sprite_map

class GamePiece(Sprite):

    def __init__(self, id_, position, type_, value, texturehandler):
        super(self.__class__, self).__init__(texturehandler.texture)
        self.id = id_
        self.type = type_
        self.position = position
        self.value = value

        # set origin to center of piece for rotations
        self.origin = self.set_texture_rect(texturehandler)
        self.position += self.origin

    def set_texture_rect(self, texturehandler):
        # TODO: Set the sprite based on type and value
        sprite_id = sprite_map[self.type]
        if not sprite_id:
            sprite_id = self.type
        self.texture_rectangle = texturehandler.get_rect(sprite_id)
        return (self.texture_rectangle.width / 2, self.texture_rectangle.height / 2) # center

    def move(self, x, y):
        super(self.__class__, self).move((x * self.texture_rectangle.width,
                                          y * self.texture_rectangle.height))
        return self

    # return battlefield map coordinates of piece
    def coord(self):
        return Vector2(int((self.position.x - self.origin.x) / self.texture_rectangle.width),
                          int((self.position.y - self.origin.y) / self.texture_rectangle.height))
