/*
Project:  Tank Commander Panic
File:  gamedriver.hpp
Author:  Leonardo Banderali
Description:  The main game logic driver.
*/

#ifndef GAMEDRIVER_HPP
#define GAMEDRIVER_HPP

// project headers
#include "playerclient.hpp"
#include "protocol/message.hpp"

void game_driver(PlayerSpool& client_spool, std::string map_file_path, protocol::MessageSpool& msg_spool);
/*  runs the game */

#endif // GAMEDRIVER_HPP
