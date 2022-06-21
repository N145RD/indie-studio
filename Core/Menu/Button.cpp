/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#include "Button.hpp"
#include <iostream>

Button::Button(const std::string &text, Vector2 position, Vector2 textOffset, Color textColour, Action action)
    : _texture("VisualLib/Spritesheet/redSheet.png", {0,0}), _sound("VisualLib/buttonfx.wav")
{
    _soundHasPlayed = false;
    _wasAClick = false;
    _lastRequestedPos = {0,0};
    _action = action;
    _text = text;
    _buttonPosition = {position.x, position.y, 190, 49};
    _textOffset = textOffset;
    _textColour = textColour;
    _normal = {0.0f, 45.0f, 190.0f, 49.0f};
    _hovered = {0.0f, 139.0f, 190.0f, 49.0f};
    _clicked = {0.0f, 0.0f, 190.0f, 45.0f};
}

Button::Button(const std::string &text, const std::string &filePath, const std::string &soundPath, Vector2 position, Vector2 textOffset, Color textColour, Action action, Rectangle normal, Rectangle hovered, Rectangle clicked)
    : _texture(filePath, {0,0}), _sound(soundPath)
{
    _soundHasPlayed = false;
    _wasAClick = false;
    _action = action;
    _text = text;
    _buttonPosition = {position.x, position.y, 190, 49};
    _textOffset = textOffset;
    _textColour = textColour;
    _normal = normal;
    _hovered = hovered;
    _clicked = clicked;
}

void Button::draw()
{
    if (this->isInButton(_lastRequestedPos, _wasAClick) && !_wasAClick) {
        _texture.drawRec(_hovered, (Vector2){_buttonPosition.x, _buttonPosition.y});
    } else if (this->isInButton(_lastRequestedPos, _wasAClick) && _wasAClick) {
        _texture.drawRec(_clicked, (Vector2){_buttonPosition.x, _buttonPosition.y});
    } else {
        _texture.drawRec(_normal, (Vector2){_buttonPosition.x, _buttonPosition.y});
    }
    DrawText(_text.c_str(), _buttonPosition.x + _textOffset.x, _buttonPosition.y + _textOffset.y, 20, _textColour);
}

bool Button::isInButton(Vector2 position, bool click)
{
    _lastRequestedPos = position;
    _wasAClick = click;
    if (_buttonPosition.x < position.x && _buttonPosition.x + _buttonPosition.width > position.x
     && _buttonPosition.y < position.y && _buttonPosition.y + _buttonPosition.height > position.y)
        return true;
    _soundHasPlayed = false;
    return false;
}

Action Button::getAction()
{
    return _action;
}

void Button::playSound()
{
    if (!_soundHasPlayed && !_sound.isSoundPlaying())
        _sound.playSound();
    _soundHasPlayed = true;
}
