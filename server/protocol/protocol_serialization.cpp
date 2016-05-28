/*
Project:  Tank Commander Panic
File:  protocol_serialization.hpp
Author:  Leonardo Banderali
Description:  Implementation of functions needed to make protocol types serializable.
*/

#include "protocoldefs.hpp"

namespace protocol {

unsigned char get_byte(protocol::Action a, std::size_t n) {
    return serial::get_byte(static_cast<char>(a), n);
}

unsigned char get_byte(protocol::Direction d, std::size_t n) {
    return serial::get_byte(static_cast<char>(d), n);
}

void set_byte(protocol::Action& var, std::size_t n, serial::byte val) {
  serial::set_byte(reinterpret_cast<unsigned char&>(var), n , val);
}

void set_byte(protocol::Direction& var, std::size_t n, serial::byte val) {
  serial::set_byte(reinterpret_cast<unsigned char&>(var), n , val);
}

}
