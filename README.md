# CPSC 441 Assignment 2

## Overview

The coding portion of Assignment 2 was completed in C++ 14 using the Boost
libraries and Python 3. See Section XI Plan for where this submission fits into
the development of the entire project.

## Dependencies

- `Boost (1.56 or greater)` is required to compile and run these programs. Both
the development headers and binaries may be installed using the preferred
package manager of your Linux distribution.
- `gcc (v4.9 or greater)` is required to support C++ 14.
- `Python 3.*` is required for running the python client.

## Building
The server and client can be compiled with a provided script:

`./build`

## Running
To run the TCP/UDP Server:

`./SelectServer <port>`

To run the C++ TCP Client:

`./TCPClientCPP <host ip> <port>`

To run the Python TCP Client:

`./TCPClientPy <host ip> <port>`

## Troubleshooting

If you have any difficulties compiling or running these programs, please let us
(Group 36) know so that we can demonstrate our assignment.

## Notes

A special, minimalistic protocol was created in order to support file transfer.
As such, the TCP server is not completely compatible with the TCP client
provided in lectures.
