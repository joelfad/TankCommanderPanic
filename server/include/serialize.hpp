/*
Project:  Tank Commander Panic
File:  serialize.hpp
Author:  Leonardo Banderali
Description:  Generic templates and functions for serializing data.
*/

#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <array>

namespace serial {

//~serialization types~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

using byte = unsigned char;
template<std::size_t N> using byte_array = std::array<byte, N>;



//~utility templates~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Gives the combined size off all types specified as template parameters
*/
template <typename T, typename... Ts> struct total_size {
    static constexpr std::size_t size = sizeof(T) + total_size<Ts...>::size;
};
template <typename T> struct total_size<T> {
    static constexpr std::size_t size = sizeof(T);
};

/*
Given a value, returns the n'th byte of that value (counted from 0).
*/
template <typename T> auto get_byte(T val, std::size_t n) noexcept -> byte {
    constexpr auto type_size = sizeof(T);
    constexpr auto bit_count = (type_size - 1) * 8;
    return static_cast<byte>((val >> (bit_count - n*8)) & 0xff);
}

/*
Given a variable, sets the n'th byte of that variable (counted from 0) to the specified value.
*/
template <typename T> void set_byte(T& var, std::size_t n, byte val) {
    constexpr auto type_size = sizeof(T);
    constexpr auto bit_count = (type_size - 1) * 8;
    var &= ~(static_cast<T>(0xff) << (bit_count - n*8));
    var |= static_cast<T>(val) << (bit_count - n*8);
}



//~serialization functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Given a value and an iterator, this function serializes the value in big-endian byte ordering and
puts each serialized byte into the data structure pointed to by the iterator. Each time a byte is
entered into the data structure, the iterator is moved forward. The number of available entries
in the data structure, starting with and including the one being pointed to by the iterator, must
be equal to or greater than the number of bytes used to store the value being serialized.
*/
template <typename OutputIterator, typename T> auto serialize_into(OutputIterator first, T val) {
    constexpr auto size = sizeof(T);
    for (std::size_t i = 0; i < size; ++i, ++first)
        *first = get_byte(val, i);
    return first;
}

/*
Given a series of values and an iterator, this function serializes the values in big-endian byte
ordering and puts each serialized byte into the data structure pointed to by the iterator. Each
time a byte is entered into the data structure, the iterator is moved forward. The number of
available entries in the data structure, starting with and including the one being pointed to by
the iterator, must be equal to or greater than the number of bytes used to store each value being
serialized.
*/
template <typename OutputIterator, typename T, typename... Ts> auto serialize_into(OutputIterator first, T val, Ts... rest) {
    auto next = serialize_into(first, val);
    next = serialize_into(next, rest...);
    return next;
}

/*
Takes a list of variables and serializes their values into an array of bytes. Values are stored
using big-endian byte ordering.
*/
template <typename... Ts> auto serialize(Ts... vars) {
    auto data = byte_array<total_size<Ts...>::size>{};
    serialize_into(data.begin(), vars...);
    return data;
}

/*
Takes a list of bytes as serialized data and puts the value into the variable passed. Returns
an iterator pointing to one past the last byte processed. The data structure pointed to by the
iterator is assumed to store at least the same number of bytes as the size of the variable.
*/
template <typename InputIterator, typename T> auto deserialize_into(InputIterator first, T& var) {
    constexpr auto size = sizeof(T);
    for (std::size_t i = 0; i < size; ++i, ++first)
        set_byte(var, i, *first);
    return first;
}

/*
Takes a list of bytes as serialized data and puts the values into the variables listed. Returns
an iterator pointing to one past the last byte processed. The data structure pointed to by the
iterator is assumed to store at least the same number of bytes as the size of all variables.
*/
template <typename InputIterator, typename T, typename... Ts> auto deserialize_into(InputIterator first, T& var, Ts&... rest) {
    auto next = deserialize_into(first, var);
    next = deserialize_into(next, rest...);
    return next;
}

} // namespace serialize

#endif // SERIALIZE_HPP
