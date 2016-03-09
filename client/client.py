#!/usr/bin/python3

# Project: CPSC 441, Assignment 2 (python-client)
# File: client.py
# Author: Joel McFadden
# Created: February 2, 2016
# Modified: March 6, 2016

# Credits: Part of this code has been adapted from the following book:
#          "Learning Python Network Programming" © 2015 Packt Publishing

import sys
import socket
import re

BUFSIZ = 1024

if __name__ == '__main__':
    # check command line arguments
    if len(sys.argv) != 3:
        print("Usage: tcp_client_py <host> <port>\n")
        sys.exit()

    try:
        # create tcp socket
        host = sys.argv[1]
        port = int(sys.argv[2])

        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock_addr = (host, port)
        client_sock.connect(sock_addr)

        while True:
            # request input from user
            request = input("Please enter a message to be sent to the server "
                            "'logout' to terminate): ")

            # send message to the server
            client_sock.send(request.encode('utf-8'))

            # handle quit messages
            if request == 'logout' or request == 'terminate':
                break

            # get header from server
            reply_length = int(client_sock.recv(4))
            status_code = int(client_sock.recv(1))

            # get reply from server
            reply = client_sock.recv(reply_length).decode("unicode_escape")

            # handle specific server responses based on entered commands
            if re.match("get [A-Za-z_ /.]+\\s*", request) and status_code == 0:
                # save file
                file_name = '{0}-{1}'.format(request[4:], client_sock.getsockname()[1])
                f = open(file_name, mode='w', encoding='utf-8')
                f.write(reply)
                f.close()
                print('File saved in {0} ({1} bytes)'.format(file_name, reply_length))
            else:
                print(reply, end='')

    except KeyboardInterrupt:
        print("Exited by user")

    client_sock.close()
