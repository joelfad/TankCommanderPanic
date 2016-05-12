#!/usr/bin/python3

# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: client.py
# Author: Joel McFadden
# Created: February 2, 2016
# Modified: April 4, 2016

# Credits: Part of this code has been adapted from the following book:
#          "Learning Python Network Programming" © 2015 Packt Publishing

from game import *

if __name__ == '__main__':
    # check command line arguments
    if len(sys.argv) != 2:
        print("Usage: {} <HOST>".format(sys.argv[0]))
        print("HOST is the IP address of the game server")
        sys.exit()

    # set server address
    server_addr = (sys.argv[1], 4410)

    game = Game(server_addr)
    game.run()
