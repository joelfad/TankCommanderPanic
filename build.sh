#!/bin/bash
# This script is provided to automate building the TCP/UDP Server and TCP Client
# for CPSC 441 Assignment 1. It was created by Team 36 on Feb. 5, 2016.

# Build the TCP/UDP Server
echo "Building TCP/UDP Server..."
cd server
cmake .
make
ln -s server/server ../SelectServer

# Build the TCP Client
echo "Building TCP Client..."
cd ../tcp_client_cpp
cmake .
make
ln -s tcp_client_cpp/tcp_client_cpp ../TCPClient
