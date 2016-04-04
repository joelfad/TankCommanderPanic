#!/usr/bin/python3

# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: client.py
# Author: Joel McFadden
# Created: February 2, 2016
# Modified: March 31, 2016

# Credits: Part of this code has been adapted from the following book:
#          "Learning Python Network Programming" © 2015 Packt Publishing

from game import *

if __name__ == '__main__':
    game = Game()
    game.set_state() # TODO: Remove after game gets state from Game State Message
    game.run()
