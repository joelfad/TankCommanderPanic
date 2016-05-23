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



//~serialization functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Given a value and an iterator, this function serializes the value in big-endian byte ordering and
puts each serialized byte into the data structure pointed to by the iterator. Each time a byte is
entered into the data structure, the iterator is moved forward. The number of available entries
in the data structure, starting with and including the one being pointed to by the iterator, must
be equal to or greater than the number of bytes used to store the value being serialized.
*/
template <typename OutputIterator, typename T> auto serialize_into(OutputIterator data, T val) {
    constexpr auto size = sizeof(T);
    for (std::size_t i = 0; i < size; ++i, ++data)
        *data = get_byte(val, i);
    return data;
}

/*
Given a series of values and an iterator, this function serializes the values in big-endian byte
ordering and puts each serialized byte into the data structure pointed to by the iterator. Each
time a byte is entered into the data structure, the iterator is moved forward. The number of
available entries in the data structure, starting with and including the one being pointed to by
the iterator, must be equal to or greater than the number of bytes used to store each value being
serialized.
*/
template <typename OutputIterator, typename T, typename... Ts> auto serialize_into(OutputIterator data, T val, Ts... rest) {
    auto new_data = serialize_into(data, val);
    new_data = serialize_into(new_data, rest...);
    return new_data;
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

} // namespace serialize

#endif // SERIALIZE_HPP
