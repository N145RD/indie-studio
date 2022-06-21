/*
** EPITECH PROJECT, 2022
** Errors
** File description:
** example of bad code:
*/

#pragma once

#include <string>
#include <exception>

class Error : public std::exception {
    std::string _message;
    public:
        Error(std::string const &message);
        const char *what(void) const noexcept;
};
