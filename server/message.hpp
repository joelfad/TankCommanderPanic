/*
Project:  Tank Commander Panic
File:  messagespool.hpp
Author:  Leonardo Banderali
Description:  A synchronized spool for passing messages between a PlayerClient the GameDriver.
*/

#ifndef MESSAGESPOOL_HPP
#define MESSAGESPOOL_HPP

// project headers
#include "spool.hpp"
#include "playerclient.hpp"

// c++ standard libraries
#include <string>

using MessageSpool = spool<std::string>;

#endif // MESSAGESPOOL_HPP
