/*
 * Project: server
 * File: $PATH
 * Author: Kurtis Jantzen
 * Description: 
 */

#ifndef SERVER_MESSAGEENVELOPE_HPP
#define SERVER_MESSAGEENVELOPE_HPP

enum class Recipient {
    ALL, ACTOR, TARGET
};

class MessageEnvelope {
public:
    MessageEnvelope(Recipient recipient, protocol::Message message) : recipient(recipient), message(message) { };

    MessageEnvelope(Recipient recipient, protocol::PlayerID receiver, protocol::Message message) :
            recipient(recipient), receiver(receiver), message(message) { };

    auto get_recipient() const noexcept { return this->recipient; }

    auto get_message() const noexcept { return this->message; }

    auto get_receiver() const noexcept { return this->receiver; }

private:

    Recipient recipient;

    protocol::Message message;

    protocol::PlayerID receiver;

};


#endif //SERVER_MESSAGEENVELOPE_HPP
