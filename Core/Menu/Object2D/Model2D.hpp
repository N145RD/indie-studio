/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#pragma once

#include "raylib.h"
#include <iostream>
#include <cstring>
#include <string>

class Model2D {
    protected:
        Texture2D _texture;
        Vector2 _position;
        Color _color = WHITE;
        Rectangle _rect;
    public:
        virtual ~Model2D() = default;

        virtual void draw();
};
