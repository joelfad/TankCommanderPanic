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
#include <vector>

namespace protocol {

class Message {
    public:
        Message(char* bytes, int _size) {
            msg_content.reserve(_size);
            for (int i = 0; i < _size; i++)
                msg_content.push_back(bytes[i]);
        }

        auto size() {
            return msg_content.size();
        }

        const unsigned char* data() const {
            return msg_content.data();
        }

    private:
        std::vector<unsigned char> msg_content;
};

using MessageSpool = spool<Message>;

}

#endif // MESSAGESPOOL_HPP
