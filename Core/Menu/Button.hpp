/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#pragma once

#include "raylib.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "ButtonEvent.hpp"
#include "Object2D/Sprite.hpp"
#include "../../Music/ISound.hpp"

class Button {
    protected:
        Rectangle _buttonPosition;
        Vector2 _textOffset;
        std::string _text;
        Color _textColour;
        Sprite _texture;
        Rectangle _normal;
        Rectangle _hovered;
        Rectangle _clicked;
        Vector2 _lastRequestedPos;
        Action _action;
        ISound _sound;
        bool _soundHasPlayed;
        bool _wasAClick;
    public:
        Button(const std::string &text, Vector2 position, Vector2 textOffset, Color textColour, Action action);
        Button(const std::string &text, const std::string &filePath, const std::string &soundPath, Vector2 position, Vector2 textOffset, Color textColour, Action action, Rectangle normal, Rectangle hovered, Rectangle clicked);

        virtual void draw();
        virtual bool isInButton(Vector2 position, bool click);
        virtual Action getAction();
        void playSound();
};
