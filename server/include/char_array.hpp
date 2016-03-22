/*
Project:  Server
File:  char_array.hpp
Author:  Leonardo Banderali
Description:  This file contains a small class representing an array of chars.
    It is provided for convenience to avoid having to use a `char[]`.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#ifndef CHAR_ARRAY_HPP
#define CHAR_ARRAY_HPP



// c++ standard libraries
#include <array>
#include <cstring>
#include <string>
#include <iostream>



//~template class declaration~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
As the name suggests, the `char_array` class represents an array of chars (`char[]`).
The template parameter `N` specifies the number of characters (elements) in the array.
*/
template <std::size_t N>
class char_array : public std::array<char, N> {
    public:
        char_array();

        void copy(const char* str) noexcept;
        /*  copy value from c style string */

        void copy(const std::string& str) noexcept;
        /*  copy value from string */

        void clear() noexcept;
        /*  set all characters to '\0' */

        void set_null(int i) noexcept;
        /*  set character `i` to '\0' */

        std::size_t length() const noexcept;
        /*  returns the string length of the data */
};



//~operator overloads~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <std::size_t N>
std::ostream& operator << (std::ostream& os, const char_array<N>& chars) {
    return os << chars.data();
}

template <std::size_t N>
bool operator == (char_array<N> chars_a, char_array<N> chars_b) {
    return strncmp(chars_a.data(), chars_b.data(), N) == 0;
}

template <std::size_t N>
bool operator == (char_array<N> chars_a, const char* chars_b) {
    return strncmp(chars_a.data(), chars_b, N) == 0;
}

template <std::size_t N>
bool operator == (const char* chars_a[], char_array<N> chars_b) {
    return strncmp(chars_a, chars_b.data(), N) == 0;
}



//~template function implementation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <std::size_t N>
char_array<N>::char_array() : std::array<char, N>{} {}

/*
copy value from c style string
*/
template <std::size_t N>
void char_array<N>::copy(const char* str) noexcept {
    strncpy(this->data(), str, N);
}

/*  copy value from string */
template <std::size_t N>
void char_array<N>::copy(const std::string& str) noexcept {
    copy(str.c_str());
}

/*
set all characters to '\0'
*/
template <std::size_t N>
void char_array<N>::clear() noexcept {
    for (auto& c : *this) {
        c = '\0';
    }
}

/*
set character `i` to '\0'
*/
template <std::size_t N>
void char_array<N>::set_null(int i) noexcept {
    if (i >=0 && i < N)
        (*this)[i] = '\0';
}

/*
returns the string length of the data
*/
template <std::size_t N>
std::size_t char_array<N>::length() const noexcept {
    return strlen(this->data());
}

#endif // CHAR_ARRAY_HPP
