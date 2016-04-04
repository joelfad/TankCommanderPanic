/*
 * Project: Tank Commander Panic
 * File: gamemodelerror.hpp
 * Author: Kurtis Jantzen
 * Description: Types representing game model errors.
 */

#ifndef SERVER_GAMEMODELERROR_HPP
#define SERVER_GAMEMODELERROR_HPP

#include <string>
#include <stdexcept>

namespace game_model {

class GameModelEventError : public std::logic_error {
    public:
        explicit GameModelEventError(const std::string& _error) : std::logic_error{_error} {}
        explicit GameModelEventError(const char* _error) : std::logic_error{_error} {}
};

class GamePieceNotFoundError : public std::logic_error {
public:
    explicit GamePieceNotFoundError(const std::string& _error) : std::logic_error{_error} {}
    explicit GamePieceNotFoundError(const char* _error) : std::logic_error{_error} {}
};

}

#endif //SERVER_GAMEMODELERROR_HPP
