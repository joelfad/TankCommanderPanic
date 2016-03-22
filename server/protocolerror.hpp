/*
Project:  Tank Commander Panic
File:  protocolerror.hpp
Author:  Leonardo Banderali
Description:  Types representing protocol errors.
*/

#ifndef PROTOCOLERROR_HPP
#define PROTOCOLERROR_HPP

#include "message.hpp"

#include <string>
#include <stdexcept>

namespace protocol {

class ProtocolError : public std::runtime_error {
    public:
        explicit ProtocolError(const std::string& _error) : std::runtime_error{_error} {}
        explicit ProtocolError(const char* _error) : std::runtime_error{_error} {}
};

class MessageFormatError : public ProtocolError {
    public:
        MessageFormatError(const std::string& _error, const Message& _message) : ProtocolError{_error}, msg{_message} {}
        MessageFormatError(const char* _error, const Message& _message) : ProtocolError{_error}, msg{_message} {}

        auto message() const noexcept -> Message {
            return msg;
        }

    private:
        Message msg;
};

class MessageLengthError : public MessageFormatError {
    public:
        MessageLengthError(const std::string& _error, const Message& _message) : MessageFormatError{_error, _message} {}
        MessageLengthError(const char* _error, const Message& _message) : MessageFormatError{_error, _message} {}
};

}

#endif // PROTOCOLERROR_HPP
