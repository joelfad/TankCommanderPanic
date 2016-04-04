# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: messagehandler.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 3, 2016

import sys
import socket
import select
import struct

class MessageHandler:

    def __init__(self, game, server_addr):
        self.game = game

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
        message_actions[message_type](message_type)

    def send_message(self, action_type, direction=0, piece_id=0):
        # pack message into binary
        message = struct.pack('<HBBi', self.game.player_id, action_type, direction, piece_id)

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
        '''.format(self.game.player_id, action_type, direction, piece_id))

    def check_for_messages(self):
        print("Checking for new messages...")

        # poll for incoming messages
        for fd, event in self.poll.poll(250): # wait 250ms for events
            if event & select.POLLIN:
                self.recv_message()

    def shutdown(self):
        print("Closing connection.")
        self.sock.close()

    def unpack_game_state(self):
        # receive first three bytes of message
        message_part = self.sock.recv(5)
        map_id, map_version, player_id, owned_tank_count = struct.unpack('<BBHB', message_part)

        # receive remainder of message
        message_part = self.sock.recv(owned_tank_count * 4)
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

        return (map_id, map_version, player_id, tank_piece_id)

    def unpack_create_piece(self):
        # receive message
        message = self.sock.recv(10)
        value, piece_id, piece_coord_x, piece_coord_y = struct.unpack('<iiBB', message)

        # print results
        print('''\
        -- Received --
        <Create Piece Message>
        value = {}
        piece_id = {}
        piece_coord_x = {}
        piece_coord_y = {}\
        '''.format(value, piece_id, piece_coord_x, piece_coord_y))

        return (value, piece_id, piece_coord_x, piece_coord_y)

    def unpack_event(self):
        # receive message
        message = self.sock.recv(9)
        direction, value, piece_id = struct.unpack('<Bii', message)

        # print results
        print('''\
        -- Received --
        <Event Message>
        direction = {}
        value = {}
        piece_id = {}\
        '''.format(direction, value, piece_id))

        return (direction, value, piece_id)

    # set game state
    def receive_game_state(self, message_type):
        map_id, map_version, player_id, tank_piece_id = self.unpack_game_state()
        # TODO: handle message

    # create new game piece
    def receive_brick_piece(self, piece_type):
        value, piece_id, piece_coord_x, piece_coord_y = self.unpack_create_piece()
        # TODO: handle message

    def receive_health_piece(self, piece_type):
        value, piece_id, piece_coord_x, piece_coord_y = self.unpack_create_piece()
        # TODO: handle message

    def receive_ammo_piece(self, piece_type):
        value, piece_id, piece_coord_x, piece_coord_y = self.unpack_create_piece()
        # TODO: handle message

    def receive_decoration_piece(self, piece_type):
        value, piece_id, piece_coord_x, piece_coord_y = self.unpack_create_piece()
        # TODO: handle message

    def receive_tank_piece(self, piece_type):
        value, piece_id, piece_coord_x, piece_coord_y = self.unpack_create_piece()
        # TODO: handle message

    # handle event
    def update_ammo(self, event_type):
        direction, value, piece_id = self.unpack_event()
        # TODO: handle message

    def update_heath(self, event_type):
        direction, value, piece_id = self.unpack_event()
        # TODO: handle message

    def destroy_piece(self, event_type):
        direction, value, piece_id = self.unpack_event()
        # TODO: handle message

    def move_piece(self, event_type):
        direction, value, piece_id = self.unpack_event()
        # TODO: handle message

    def game_over(self, event_type):
        direction, value, piece_id = self.unpack_event()
        # TODO: handle message

    # map message type to functions
    message_actions = [None] * 256

    # game state actions
    message_actions[1]      = receive_game_state

    # create piece actions
    message_actions[2:8]    = [receive_brick_piece] * (8 - 2)
    message_actions[8]      = receive_health_piece
    message_actions[9]      = receive_ammo_piece
    message_actions[10]     = receive_decoration_piece
    message_actions[16:32]  = [receive_tank_piece] * (32 - 16)

    # event actions
    message_actions[32]     = update_ammo
    message_actions[33]     = update_heath
    message_actions[34]     = destroy_piece
    message_actions[35]     = move_piece
    message_actions[36]     = game_over

    message_actions = tuple(message_actions)
