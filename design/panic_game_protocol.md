# Panic Game Protocol

This document describes the message format and order for Panic Game Protocol,
the protocol used by Tank Commander Panic.

This is version `1` of the protocol.

## Client Messages

There is one message format for messages sent from the client.

### Action Message

This message is sent to inform the server of the player's attempt to take an
action such as move, shoot, or quit. The message format is as follows.

| field         | size    | description                                         |
|---------------|---------|-----------------------------------------------------|
| `player_id`   | 2 bytes | player's id number, identifies the client           |
| `action_type` | 1 byte  | enum: `attempt to move`, `attempt to shoot`, `quit` |
| `direction`   | 1 byte  | enum: `N`, `S`, `E`, `W` (not used when quitting)   |
| `piece_id`    | 4 bytes | GamePiece id number (not used when quitting)        |
| **Total**     | 8 bytes |

## Server Messages

There are three formats for messages sent by the server. The first field (1
byte) for all server messages identifies the format of the message and also
carries other information.

### Game State Message

The first format is identified by a `message_type` value of `1`. This message is
followed by Create Piece messages to populate the map. Existing GamePieces are
discarded by the client when this type of message is received.

| field | size | description |
|-|-|-|
| `message_type` | 1 byte | `1` |
| `map_id` | 1 byte | the map id number |
| `map_version` | 1 byte | the version number of the map |
| `owned_tank_count` | 1 byte | number of tanks controlled by this user, N |
| `tank_piece_id` | 4 bytes (xN tanks) | GamePiece id number of the tank |
| **Total** | 4 + 4N bytes |

### Create Piece Message

This format is identified by a `message_type` value of `2` - `31`. It describes
the creation of a new GamePiece.

| field | size | description |
|-|-|-|
| `message_type` / `piece_type` | 1 byte | `2` - `31` (see below) |
| `value` | 4 bytes | (see below) |
| `piece_id` | 4 bytes | GamePiece id number |
| `piece_coord_x` | 1 byte | x coordinate of the new GamePiece |
| `piece_coord_y` | 1 byte | y coordinate of the new GamePiece |
| **Total** | 11 bytes |

`piece_type` is the type of GamePiece and also describes aspects of the
GamePiece itself. The `value` field's meaning also differs depending of the type of
GamePiece:

| GamePiece type | meaning of `piece_type` | meaning of `value` |
|-|-|-|
| Tank | team color and style | health (used to determine sprite and display health bars in HUD) |
| Brick | style | health (used to determine sprite) |
| Health | - | amount (used to determine sprite) |
| Ammo | - | amount (used to determine sprite) |
| Decoration | style/sprite | `0` (not used) |

### Event Message

This format is identified by a `message_type` value of `64` - `255`.

| field | size | description |
|-|-|-|
| `message_type` / `event_type` | 1 byte | `64` - `255` (see below) |
| `direction` | 1 byte | enum: `N`, `S`, `E`, `W` (see below) |
| `value` | 4 bytes | (see below) |
| `piece_id` | 4 bytes | GamePiece id number |
| **Total** | 10 bytes |

`event_type` is an enum of the type of event (from the following table). The
`value` field's meaning differs depending of the type of event:

| event type | meaning of `value` | other notes |
|-|-|-|
| Update Ammo | new ammo count | `piece_id` is not specified |
| Update Health | new health value | - |
| Destroy GamePiece | `0` (not used) | - |
| Move GamePiece | distance GamePiece is moved | Only time `direction` is specified |
| Game Over | enum: `you win`, `you loose` | `piece_id` is not specified |
