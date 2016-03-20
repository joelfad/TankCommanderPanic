/*
Project:  Tank Commander Panic
File:  message.hpp
Author:  Leonardo Banderali
Description:  Simple type for representing communication messages.
*/

#ifndef MESSAGESPOOL_HPP
#define MESSAGESPOOL_HPP

// project headers
#include "spool.hpp"

// c++ standard libraries
#include <string>

namespace protocol {

using Message = std::string;

using MessageSpool = spool<Message>;

}

#endif // MESSAGESPOOL_HPP
