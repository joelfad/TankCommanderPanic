# Panic Game Protocol

This document describes the message format and order for Panic Game Protocol,
the protocol used by Tank Commander Panic. It is built on TCP and allows for
joining games and supports the gameplay.

This is version `1` of the protocol.

## Message Formats

### Client Messages

There is one message format for messages sent from the client.

#### Action Message

This message is sent to inform the server of the player's attempt to take an
action such as move, shoot, or quit. The message format is as follows.

| field         | size    | description                                         |
|---------------|---------|-----------------------------------------------------|
| `player_id`   | 2 bytes | player's id number, identifies the client           |
| `action_type` | 1 byte  | enum: `attempt to move`, `attempt to shoot`, `quit` |
| `direction`   | 1 byte  | enum: `N`, `S`, `E`, `W` (not used when quitting)   |
| `piece_id`    | 4 bytes | `GamePiece` id number (not used when quitting)      |
| **Total**     | 8 bytes |

### Server Messages

There are three formats for messages sent by the server. The first field (1
byte) for all server messages identifies the format of the message and also
carries other information.

#### Game State Message

The first format is identified by a `message_type` value of `1`. This message is
followed by Create Piece messages to populate the map. Existing `GamePiece`s are
discarded by the client when this type of message is received.

| field              | size               | description                                |
|--------------------|--------------------|--------------------------------------------|
| `message_type`     | 1 byte             | `1`                                        |
| `map_id`           | 1 byte             | the map id number                          |
| `map_version`      | 1 byte             | the version number of the map              |
| `player_id`        | 2 bytes            | player's id number, identifies the client  |
| `owned_tank_count` | 1 byte             | number of tanks controlled by this user, N |
| `tank_piece_id`    | 4 bytes (xN tanks) | `GamePiece` id number of the tank          |
| **Total**          | 6 + 4N bytes       |

#### Create Piece Message

This format is identified by a `message_type` value of `2` - `31`. It describes
the creation of a new `GamePiece`.

| field                         | size     | description                         |
|-------------------------------|----------|-------------------------------------|
| `message_type` / `piece_type` | 1 byte   | `2` - `31` (see below)              |
| `value`                       | 4 bytes  | (see below)                         |
| `piece_id`                    | 4 bytes  | `GamePiece` id number               |
| `piece_coord_x`               | 1 byte   | x coordinate of the new `GamePiece` |
| `piece_coord_y`               | 1 byte   | y coordinate of the new `GamePiece` |
| **Total**                     | 11 bytes |

`piece_type` is the type of `GamePiece` and also describes aspects of the
`GamePiece` itself. The `value` field's meaning also differs depending of the type
of `GamePiece`:

| `GamePiece` type | meaning of `piece_type` | meaning of `value`                                               |
|------------------|-------------------------|------------------------------------------------------------------|
| Tank             | team color and style    | health (used to determine sprite and display health bars in HUD) |
| Brick            | style                   | health (used to determine sprite)                                |
| Health           | -                       | amount (used to determine sprite)                                |
| Ammo             | -                       | amount (used to determine sprite)                                |
| Decoration       | style/sprite            | `0` (not used)                                                   |

#### Event Message

This format is identified by a `message_type` value of `64` - `255`.

| field                         | size     | description                          |
|-------------------------------|----------|--------------------------------------|
| `message_type` / `event_type` | 1 byte   | `64` - `255` (see below)             |
| `direction`                   | 1 byte   | enum: `N`, `S`, `E`, `W` (see below) |
| `value`                       | 4 bytes  | (see below)                          |
| `piece_id`                    | 4 bytes  | `GamePiece` id number                |
| **Total**                     | 10 bytes |

`event_type` is an enum of the type of event (from the following table). The
`value` field's meaning differs depending of the type of event:

| event type          | meaning of `value`             | other notes                        |
|---------------------|--------------------------------|------------------------------------|
| Update Ammo         | new ammo count                 | `piece_id` is not specified        |
| Update Health       | new health value               | -                                  |
| Destroy `GamePiece` | `0` (not used)                 | -                                  |
| Move `GamePiece`    | distance `GamePiece` is moved  | Only time `direction` is specified |
| Game Over           | enum: `you win`, `you loose`   | `piece_id` is not specified        |

### Message Field Sizes

The sizes of message fields were chosen to reflect the range of possible values
each field could possibly take on with future versions of Tank Commander Panic
in mind. We chose to keep the sizes as multiples of whole bytes so that parsing
and interpreting the message formats across languages could be simplified. We
chose the numbers of bytes to match the size of corresponding existing variables
in the server system for some fields and for others we based it on a realistic
number of possibilities.

We left the `32` - `63` range of the `message_type` field free so that it could
be used for some sort of new message type with a different format in the future.

## Message Order

The order of messages follows two main scenarios: connecting (or reconnecting)
to a game and making a move in the game. Connecting to a game (or reconnecting
to it after loosing a connection) starts a sequence of messages from the server
to the client to bring the client "up to speed" on the state of the game. Making
a move in the game involves sending an action to the server and receiving the
resulting event which is often sent to the other clients as well.

### Connecting to a Game

In this early version of the protocol, when a client connects, if the server is
expecting a new player, this client is assigned to a player with a unique
`player_id`. This is used to identify the players even if their connection is
broken.

The first message sent is a **Game State Message**. It tells the client which
map the game is on (`map_id` and `map_version`) as well as information the
client will need to use for the UI (`owned_tank_count` and `tank_piece_id`'s)
and for communication (`player_id`).

This message is accompanied by a following **Event Message**. It is for an
*Update Ammo* event to tell the client how much ammo the player has.

These messages are followed by a series of **Create Piece Messages**. These
messages populate the map with the `GamePiece`s the game is played with.

#### Connecting to a Full Game

If all players have clients assigned to them, a connecting client will be
assigned a new unique `player_id` which is not connected to a player in the
game. The `owned_tank_count` in the resulting **Game State Message** will be 0.
This is equivalent to being a defeated player who is allowed to continue to
watch the game as the surviving players move on.

#### Reconnecting After a Lost or Broken Connection

If a player's connection is broken and a client later connects, it will, soon
after connecting, send an **Action Message** of any kind which will include the
`player_id` in the message. This will allow the server to associate the new
connection to the original player.

### Making Moves

When the user presses a key to make a move in the client program, like driving a
tank or shooting, the client sends an **Action Message** to the server. This
message is a request to the server to see if the player can drive in the
direction requested or what will happen if the player's tank attempt to fire in
a given direction.

The response is one or more **Event Messages** sent by the server to one
or all of the clients. For example, if a tank moves successfully, the movement
of the tank will be sent to all clients so that this change can be presented to
all players. Another example is if a tank fires and hits another tank, two
messages will be sent. The first is an *Update Health* event for the tank that
was hit (sent to all clients) and the second is an *Update Ammo* event (sent tho
the client of the player to fired their gun).
