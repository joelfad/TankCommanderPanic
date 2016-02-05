# CPSC 441 Assignment 1

## Overview
The coding portion of Assignment 1 was completed in C++ 14 using the Boost libraries since these are some of the primary technologies we will be using for our term project.

## Dependencies
- `Boost (1.56 or greater)` is required to compile and run these programs. Both the development headers and binaries may be installed using the preferred package manager of your Linux distribution.
- `gcc (v4.9 or greater)` is required to support C++ 14.

## Building
The server and client can be compiled with a provided script:<br>
`./build`

## Running
To run the TCP/UDP Server:<br>
`./SelectServer <port>`

To run the TCP Client:<br>
`./TCPClient <host ip> <port>`

## Troubleshooting
If you have any difficulties compiling or running these programs, please let us (Group 36) know so that we can demonstrate our assignment.

## Notes
A special, minimalistic protocol was created in order to support file transfer. As such, the TCP server is not completely compatible with the TCP client provided in lectures.

