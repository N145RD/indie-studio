/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Event.cpp
*/

#include "Event.hpp"
#include <iostream>

Event::Event()
{
    _keypose = GetMousePosition();
    _k = GetKeyPressed();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        _i = true;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        _j = true;
    if (_i || _j)
        std::cout << "Got mouse at (" << _keypose.x << ", " << _keypose.y << ")" << std::endl;
    else if (_k != 0)
        std::cout << "Got key " << _k << " And mouse is at (" << _keypose.x << ", " << _keypose.y << ")" << std::endl;
}

bool Event::isMousePressed() const
{
    return _i;
}

bool Event::isMouseReleased() const
{
    return _j;
}

bool Event::isKeyBoard() const
{
    if (_k != 0)
        return true;
    return false;
}

Vector2 Event::getMousePos() const
{
    return _keypose;
}

int Event::getKey() const
{
    return _k;
}
