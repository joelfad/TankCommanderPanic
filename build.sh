#!/bin/bash

# Project: CPSC 441, Assignment 1
# File: build.sh
# Author: Joel McFadden
# Created: February 4, 2016
# Modified: February 4, 2016

# Description This script is provided to automate building the TCP/UDP server
#             and clients for CPSC 441 Assignment 1.

# Relative Paths
SDIR="server"
CTDIR="tcp_client_cpp"
PTDIR="tcp_client_py"
UDIR="udp_client_cpp"

# Build the TCP/UDP Server
echo "Building TCP/UDP Server..."
cmake -B$SDIR/build -H$SDIR
cd $SDIR/build && make
cd ../../

# Build the TCP Client
echo "Building TCP Client..."
cmake -B$CTDIR/build -H$CTDIR
cd $CTDIR/build && make
cd ../../

# Build the UDP Client
echo "Building UDP Client..."
cmake -B$UDIR/build -H$UDIR
cd $UDIR/build && make
cd ../../

# Create symlinks
echo "Creating symbolic links..."
ln -s $SDIR/build/server SelectServer
ln -s $CTDIR/build/tcp_client_cpp TCPClientCPP
ln -s $PTDIR/client.py TCPClientPy
ln -s $UDIR/build/udp_client_cpp UDPClient
