# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: messagehandler.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 20, 2016

import sys
import socket

class MessageHandler:
    # sock : socket

    def __init__(self, sock_addr):
        # create tcp socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(sock_addr)

    def recv_message(message):
        print("Received: {}".format(message))

    def send_message(action, dir=0, piece_id=0):
        print("Sending:\naction: {}\ndir:{}\npiece_id:{}".format(action, dir, piece_id))

    def check_for_messages():
        print("Checking for new messages...")

if __name__ == '__main__':
    # check command line arguments
    if len(sys.argv) != 3:
        print("Usage: messagehandler.py <host> <port>\n")
        sys.exit()
    try:
        message_handler = MessageHandler(sys.argv[1:3])

        while True:
            # check for messages
