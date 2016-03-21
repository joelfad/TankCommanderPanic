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
#include <tuple>

namespace protocol {

class Message {
    public:
        using size_type = std::vector<unsigned char>::size_type;

        Message(char* bytes, int _size) {
            msg_content.reserve(_size);

            for (int i = 0; i < _size; i++)
                msg_content.push_back(bytes[i]);
        }

        auto size() const noexcept -> size_type {
            return msg_content.size();
        }

        auto data() const noexcept -> const unsigned char* {
            return msg_content.data();
        }

        auto byte(size_type index) const noexcept -> unsigned char {
            return msg_content[index];
        }

    private:
        std::vector<unsigned char> msg_content;
};

using MessageSpool = spool<Message>;

}

#endif // MESSAGESPOOL_HPP
