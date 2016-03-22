/*
Project:  Tank Commander Panic
File:  server.hpp
Author:  Leonardo Banderali
Description:  The games communication server.
*/

#ifndef SERVER_HPP
#define SERVER_HPP

// project headers
#include "playerclient.hpp"
#include "message.hpp"

// c++ standard libraries
#include <memory>
#include <vector>

void server(PlayerSpool& client_spool, protocol::MessageSpool& msg_spool, unsigned short port);
/*  accepts connections from player clients and communicates with them */

#endif // SERVER_HPP
