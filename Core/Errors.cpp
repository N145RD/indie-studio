/*
** EPITECH PROJECT, 2022
** Errors
** File description:
** vim-epitech made by x4m3
*/

#include "Errors.hpp"

Error::Error(const std::string &message)
{
    _message = message;
}

const char *Error::what(void) const noexcept
{
    return _message.data();
}
