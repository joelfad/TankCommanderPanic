# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: messagehandler.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 21, 2016

import sys
import socket
import select
import struct

class MessageHandler:

    def __init__(self, server_addr):
        # create tcp socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(server_addr)
        self.poll = select.poll()
        self.poll.register(self.sock, select.POLLIN)
        client_addr = self.sock.getsockname()
        print('Listening on {}'.format(client_addr))

    def recv_message(self):
        # read message header (first byte)
        header = self.sock.recv(1)

        # check if the connection is closed
        if not header:
            print("Connection closed. Terminating.")
            self.sock.close()
            sys.exit()

        # unpack header
        message_type = struct.unpack('B', header)[0]

        # receive and process message body
        message_actions[message_type](self.sock, message_type)

    def send_message(self, action_type, direction=0, piece_id=0):
        start = time.time()
        # pack message into binary
        message = struct.pack('!HBBi', player_id, action_type, direction, piece_id)

        # send message
        self.sock.send(message)

        # print outgoing message
        print('''\
        -- Sent --
        <Action Message>
        player_id = {}
        action_type = {}
        direction = {}
        piece_id = {}\
        '''.format(player_id, action_type, direction, piece_id))

    def check_for_messages(self):
        print("Checking for new messages...")

        # poll for incoming messages
        for fd, event in self.poll.poll(250): # wait 250ms for events
            if event & select.POLLIN:
                self.recv_message()

def handle_game_state(sock, message_type):
    # receive first three bytes of message
    message_part = sock.recv(5)
    map_id, map_version, player_id, owned_tank_count = struct.unpack('!BBHB', message_part)

    # receive remainder of message
    message_part = sock.recv(owned_tank_count * 4)
    tank_piece_id = struct.unpack('!'+'i'*owned_tank_count, message_part)

    # print results
    print('''\
    -- Received --
    <Game State Message>
    map_id = {}
    map_version = {}
    player_id = {}
    owned_tank_count = {}
    tank_piece_id = {}\
    '''.format(map_id, map_version, player_id, owned_tank_count, tank_piece_id))

def handle_create_piece(sock, piece_type):
    # receive message
    message = sock.recv(10)
    value, piece_id, piece_coord_x, piece_coord_y = struct.unpack('!iiBB', message)

    # print results
    print('''\
    -- Received --
    <Create Piece Message>
    piece_type = {}
    value = {}
    piece_id = {}
    piece_coord_x = {}
    piece_coord_y = {}\
    '''.format(piece_type, value, piece_id, piece_coord_x, piece_coord_y))

def handle_event(sock, event_type):
    # receive message
    message = sock.recv(9)
    direction, value, piece_id = struct.unpack('!Bii', message)

    # print results
    print('''\
    -- Received --
    <Event Message>
    event_type = {}
    direction = {}
    value = {}
    piece_id = {}\
    '''.format(event_type, direction, value, piece_id))

# populate message actions list with functions
message_actions = [None] * 256
message_actions[1] = handle_game_state
message_actions[2:32] = [handle_create_piece] * (32 - 2)
message_actions[64:256] = [handle_event] * (256 - 64)
message_actions = tuple(message_actions)

# global variable
player_id = 12345

if __name__ == '__main__':
    # check command line arguments
    if len(sys.argv) != 3:
        print("Usage: messagehandler.py <host> <port>\n")
        sys.exit()

    # set server address
    server_addr = (sys.argv[1], int(sys.argv[2]))

    # create message handler
    message_handler = MessageHandler(server_addr)

    try:
        while True:
            # check for messages
            message_handler.check_for_messages()

    except KeyboardInterrupt:
        print("Exited by user")

    # clean up
    message_handler.sock.close()
