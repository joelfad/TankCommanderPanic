/*
Project:  Tank Commander Panic
File:  servermessagehandle.hpp
Author:  Leonardo Banderali
Description:  A handle for messages sent by the server to clients.
*/

#ifndef SERVERMESSAGEHANDLE_HPP
#define SERVERMESSAGEHANDLE_HPP

#include "message.hpp"

namespace protocol {

class ServerMessageHandle {
    public:
        ServerMessageHandle();
        ~ServerMessageHandle() noexcept {}

        virtual Message to_msg() const = 0;
        /*  return message containing the fields specified by this handle */

    private:

};

}

#endif // SERVERMESSAGEHANDLE_HPP
