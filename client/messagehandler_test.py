# Project: Tank Commander Panic (client)
# Course: CPSC 441, Computer Networks
# File: messagehandler_test.py
# Author: Joel McFadden
# Created: March 20, 2016
# Modified: March 21, 2016

import sys
import socket
import struct

def create_piece():
    # sample values to send
    piece_type = 2
    value = 50
    piece_id = 2048
    piece_coord_x = 5
    piece_coord_y = 12

    # pack message into binary
    return struct.pack('!BiiBB', piece_type, value, piece_id, piece_coord_x, piece_coord_y)

def event():
    # sample values to send
    event_type = 68
    direction = 1
    value = 22
    piece_id = 5003

    # pack message into binary
    return struct.pack('!BBii', event_type, direction, value, piece_id)

def game_state():
    # sample values to send
    message_type = 1
    map_id = 4
    map_version = 2
    player_id = 54321
    owned_tank_count = 3
    tank_piece_id = [2100, 2101, 2102]

    # pack message into binary
    return struct.pack('!BBBHB'+'i'*owned_tank_count, message_type, map_id, map_version, player_id, owned_tank_count, *tank_piece_id)

if __name__ == '__main__':
    # check command line arguments
    if len(sys.argv) != 3:
        print("Usage: messagehandler_test.py <host> <port>\n")
        sys.exit()

    # set server address
    server_addr = (sys.argv[1], int(sys.argv[2]))

    # create a TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # allow the socket to forcibly use a port in use by another socket
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # bind socket to address and listen for incoming connections
    server_socket.bind(server_addr)
    server_socket.listen()


    # wait for client to connect
    print('Server waiting for connection...')
    client_sock, addr = server_socket.accept()
    print('Client connected from: ', addr)

    # send test messages to client
    input("Press [Enter] to send messages...")
    client_sock.send(create_piece())
    input("> Creating Piece")
    client_sock.send(event())
    input("> Event")
    client_sock.send(game_state())
    input("> Game State")

    # clean up
    client_sock.shutdown(socket.SHUT_RDWR)
    client_sock.close()
    server_socket.close()
