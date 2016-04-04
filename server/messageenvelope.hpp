/*
 * Project: server
 * File: $PATH
 * Author: Kurtis Jantzen
 * Description: 
 */

#ifndef SERVER_MESSAGEENVELOPE_HPP
#define SERVER_MESSAGEENVELOPE_HPP

enum class Recipient {
    ALL, ACTOR
};

class MessageEnvelope {
public:
    MessageEnvelope(Recipient recipient, protocol::Message message) : recipient(recipient), message(message) { };

    auto get_recipient() const noexcept { return this->recipient; }

    auto get_message() const noexcept { return this->message; }

private:

    Recipient recipient;

    protocol::Message message;

};


#endif //SERVER_MESSAGEENVELOPE_HPP
