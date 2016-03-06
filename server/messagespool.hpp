/*
Project:  Tank Commander Panic
File:  spool.hpp
Author:  Leonardo Banderali
Description:  A synchronized spool for passing messages between a PlayerClient the GameDriver.
*/

#ifndef MESSAGESPOOL_HPP
#define MESSAGESPOOL_HPP

// project headers
#include "spool.hpp"

// c++ standard libraries
#include <string>

using MessageSpool = spool<std::string>;

#endif // MESSAGESPOOL_HPP
