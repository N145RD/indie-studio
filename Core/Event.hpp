/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Event.hpp
*/

#include "raylib.h"

class Event {
    public:
        Event();

        bool isMousePressed() const;
        bool isMouseReleased() const;
        bool isKeyBoard() const;
        Vector2 getMousePos() const;
        int getKey() const;
    protected:
        int _x;
        int _y;
        int _k;
        bool _i = false;
        bool _j = false;
        Vector2 _keypose;

    private:
};
