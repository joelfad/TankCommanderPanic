#!/bin/bash

# Project: Tank Commander Panic
# File: build.sh
# Author: Joel McFadden
# Created: February 4, 2016
# Modified: March 8, 2016

# Description This script is provided to automate building the server
#             and clients for Tank Commander Panic

# Relative Paths
SDIR="server"
CDIR="client"

# Build the Server
echo "Building Server..."
cmake -B$SDIR/build -H$SDIR
cd $SDIR/build && make
cd ../../

# Create symlinks
echo "Creating symbolic links..."
ln -s $SDIR/build/server Server
ln -s $CDIR/client.py Client
