# .map File Format Specification

This document specifies the format and content of `.map` files for the Tank
Commander Panic game server program. These files are created by the `map_gen.py`
tool and imported by the game server.

## About Map Generator

This tool takes a `.tmx` file saved from the open-source game map creation tool
[Tiled](https://github.com/bjorn/tiled) and creates a `.map` file formatted for
import by the server program. The server program uses this file to set up the
stage at the start of a game.

## File Format

`.map` files are ascii text files (although usually utf-8 encoded) and use
unix-style line separators.

The format of the file type is as follows:

    MAP_NAME
    MAP_ID
    MAP_VERSION
    NUMBER_OF_PLAYERS
    MAP_WIDTH
    MAP_HEIGHT
    STARTING_POSITIONS [each player's starting positions on separate lines]
    [blank line]
    MAP_DATA

### Format of Header Sections

| Header Section     | Format      | Example       |
|--------------------|-------------|---------------|
| MAP_NAME           | string      | `Test`        |
| MAP_ID             | integer     | `1`           |
| MAP_VERSION        | integer     | `1`           |
| NUMBER_OF_PLAYERS  | integer     | `2`           |
| MAP_WIDTH          | integer     | `30`          |
| MAP_HEIGHT         | integer     | `20`          |
| STARTING_POSITIONS | *see below* | `1,4;1,5;1,6` |

#### Format of `STARTING_POSITIONS`

Each of a player's tanks has an `x` and `y` coordinate separated by a comma `,`
(with no spaces). Each tank's coordinates are separated by a semicolon `;` (also
with no spaces). The result is a line with the following format for a tank at
`1,2`, another at `3,4`, and a third at `5,6`:

    1,2;3,4;5,6

Multiple player's starting positions are listed on separate lines, for example
if there are four players:

    1,1;3,2;2,3
    30,1;28,2;29,3
    2,28;3,29;1,30
    28,29;29,28;30,30

### Format of `MAP_DATA`

Each tile of the map is represented by a single character. This character
describes the properties of the tile as follows:

| example | clear drive | clear shot | enum value | char  | ascii code |
|---------|:-----------:|:----------:|:----------:|:-----:|:----------:|
| wall    | false `0`   | false `0`  | `0`        | `'0'` | `0x30`     |
| water   | false `0`   | true  `1`  | `1`        | `'1'` | `0x31`     |
| foliage | true  `1`   | false `0`  | `2`        | `'2'` | `0x32`     |
| land    | true  `1`   | true  `1`  | `3`        | `'3'` | `0x33`     |

Each tile is then laid out in rows where each line of the `MAP_DATA` section is
a row of the map. For example:

    000000000000000000000000000000
    033333222333333233333322222220
    022233222332223333300322222220
    022232333222223222000333332220
    033333303222223222333332222220
    032222003222233222322232222220
    033222333322223332222232332220
    033000232233333222222233332220
    033333332222223222222232233220
    032332222222223222222322223220
    033332223333223111111332223220
    103322222202311111111113323220
    130322222333111111111113033220
    130322222311111111111113033220
    122332223111111111111112333220
    122333331111111111111111113220
    122003331111111111111111113331
    133033033333330333333303333331
    133333333303333333033333330331
    111111111111111111111111111111
