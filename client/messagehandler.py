# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: messagehandler.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: April 4, 2016

import sys
import socket
import select
import struct
from protocol import Cardinality as card
from gamestate import GameState as gs

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
        print("MESSAGE TYPE: {}".format(message_type)) # TODO: Remove this DEBUG line
        self.message_actions[message_type](self, message_type)
        if self.game.state is not gs.wait:
            self.game.hud.update()

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
        for fd, event in self.poll.poll(10): # wait 10ms for events
            if event & select.POLLIN:
                self.recv_message()

    def shutdown(self):
        print("Closing connection.")
        self.sock.close()

    def unpack_game_state(self):
        # receive first three bytes of message
        message_part = self.sock.recv(7) # TODO: This should be 5
        map_id, map_version, garbage1, player_id, owned_tank_count, garbage2 = struct.unpack('<BBBHBB', message_part)

        # receive remainder of message
        message_part = self.sock.recv(owned_tank_count * 4)
        tank_piece_ids = struct.unpack('!'+'i'*owned_tank_count, message_part)

        # print results
        print('''\
        -- Received --
        <Game State Message>
        map_id = {}
        map_version = {}
        player_id = {}
        owned_tank_count = {}
        tank_piece_ids = {}\
        '''.format(map_id, map_version, player_id, owned_tank_count, tank_piece_ids))

        return (map_id, map_version, player_id, tank_piece_ids)

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

        return (piece_id, piece_coord_x, piece_coord_y, value)

    def unpack_event(self):
        # receive message
        message = self.sock.recv(11) # TODO: This should be 9
        direction, garbage, value, piece_id = struct.unpack('<Bhii', message) # TODO: Remove garbage

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
        state = self.unpack_game_state()
        self.game.set_state(*state)

    # create new game piece
    def receive_piece(self, piece_type):
        piece_data = self.unpack_create_piece()
        self.game.battlefield.create_piece(piece_type, *piece_data)

    def receive_brick_piece(self, piece_type):
        receive_piece(piece_type)

    def receive_health_piece(self, piece_type):
        receive_piece(piece_type)

    def receive_ammo_piece(self, piece_type):
        receive_piece(piece_type)

    def receive_decoration_piece(self, piece_type):
        receive_piece(piece_type)

    def receive_tank_piece(self, piece_type):
        receive_piece(piece_type)

    # handle event
    def update_ammo(self, event_type):
        direction, value, piece_id = self.unpack_event()
        self.game.ammo = value

    def update_heath(self, event_type):
        direction, value, piece_id = self.unpack_event()
        self.game.battlefield.get_piece(piece_id).value = value

    def destroy_piece(self, event_type):
        direction, value, piece_id = self.unpack_event()
        self.game.battlefield.destroy_piece(piece_id)

    def move_piece(self, event_type):
        direction, units, piece_id = self.unpack_event()
        piece = self.game.battlefield.get_piece(piece_id)
        if direction == card.north.value:
            piece.move(0, -units).rotation = 0      # move north
        elif direction == card.east.value:
            piece.move(units, 0).rotation = 90      # move east
        elif direction == card.south.value:
            piece.move(0, units).rotation = 180     # move south
        elif direction == card.west.value:
            piece.move(-units, 0).rotation = 270    # move west
        else:
            print("Invalid move request. Unknown direction: {}".format(direction))
        self.game.center_view()

    def game_start(self, event_type):
        self.unpack_event() # dump message
        self.game.start()

    def game_over(self, event_type):
        direction, value, piece_id = self.unpack_event()
        if not value:
            self.game.state = gs.lost
        elif value == 1: # TODO: Remove magic number
            self.game.state = gs.won
        else:
            print("Invalid game over value: {}".format(value))

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
    message_actions[36]     = game_start
    message_actions[37]     = game_over

    message_actions = tuple(message_actions)
