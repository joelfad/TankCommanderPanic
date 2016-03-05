# Create Piece Message

Tank
message_piece_type  [tanktype] --> color & style
value               [health]
piece_id            [unique#]
piece_coord_x       [x]
piece_coord_y       [y]
    
Brick
message_piece_type  [bricktype] --> style
value               [health]
piece_id            [unique#]
piece_coord_x       [x]
piece_coord_y       [y]

Health
message_piece_type  [health]
value               [amount]
piece_id            [unique#]
piece_coord_x       [x]
piece_coord_y       [y]

Ammo
message_piece_type  [ammo]
value               [amount]
piece_id            [unique#]
piece_coord_x       [x]
piece_coord_y       [y]

Decoration
message_piece_type  [decorationtype] --> style/image
value               [-]
piece_id            [unique#]
piece_coord_x       [x]
piece_coord_y       [y]


---


# Event Message

Update_ammo
message_event_type  [update_ammo]
direction           [-]
value               [delta]
piece_id            [-]

Update_health
message_event_type  [update_health]
direction           [-]
value               [delta]
piece_id            [unique_solidpiece]

Destroy_gamepiece
message_event_type  [destroy_piece]
direction           [-]
value               [-]
piece_id            [unique_gamepiece]

Move_gamepiece      
message_event_type  [move_piece]
direction           [NSEW]
value               [distance]
piece_id            [unique_gamepiece]

Gameover
message_event_type  [gameover]
direction           [-]
value               [typeofending] --> you lost, you won
piece_id            [-]


---


# Game State Message

message_type        [1]
map_id              [map_id] --> which map to play the game on
map_version         [map_version] --> iteration of map design
owned_tank_count    [num_of_tanks_alive] --> how many tanks you still control
tank_piece_id       [unique_gamepiece]
tank_piece_id       [unique_gamepiece]
tank_piece_id       [unique_gamepiece] --> how many of these depends on owned_tank_count
...


---


# Action Message (from Client)

player_id           [player_id]
action_type         [action] --> attempt_move, attempt_shoot, quit
direction           [NSEW] --> (not used when quitting)
piece_id            [active_tank_piece_id] --> (not used when quitting)


---