# Tank Commander Panic

## Dependencies

- `Boost (1.56 or greater)` is required to compile and run these programs. Both
the development headers and binaries may be installed using the preferred
package manager of your Linux distribution.
- `gcc (v4.9 or greater)` is required to support C++ 14.
- `Python 3.*` is required for running the python client.

## Building
The server and client can be compiled with a provided script:

`./build.sh`

## Running
To run the Server:

`./Server <port>`

To run the Client:

`./Client <host ip> <port>`

## Troubleshooting

If you have any difficulties compiling or running these programs, please let us
(Group 36) know so that we can demonstrate our assignment.

## Development

### Gitflow

The `master` branch is for tagged releases. The `devel` branch is live
development of components outside of the server and client themselves. The
`server` and `client` branches are upstream of `devel`. They are live
development branches for their respective components.
