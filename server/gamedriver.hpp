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
#include "messagespool.hpp"

// c++ standard libraries
#include <vector>
#include <memory>

void game_driver(PlayerSpool& client_spool, MessageSpool& msg_spool);
/*  runs the game */

#endif // GAMEDRIVER_HPP
