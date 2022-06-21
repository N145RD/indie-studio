/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Texture.cpp
*/

#include "Sprite.hpp"

#include <iostream>
using namespace std;

Sprite::Sprite(const std::string& texture, Vector2 position)
{
    _position = position;
    _texture = LoadTexture(texture.c_str());
}

Sprite::Sprite(const std::string& texture, Vector2 position, Color Colour)
{
    _position = position;
    _texture = LoadTexture(texture.c_str());
    _color = Colour;
}

Sprite::~Sprite()
{
    UnloadTexture(_texture);
}

void Sprite::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

Texture2D Sprite::getTexture() const
{
    return _texture;
}

void Sprite::drawRec(Rectangle rect, Vector2 pos)
{
    _rect = rect;
    DrawTextureRec(_texture, _rect, pos, _color);
}

Vector2 Sprite::getPosition() const
{
    return _position;
}
