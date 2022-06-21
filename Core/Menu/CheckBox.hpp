#pragma once
#include "Button.hpp"

class CheckBox : public Button {
    bool _status;
    Action _offAction;
    public:
        CheckBox(const std::string &text, Vector2 position, Vector2 textOffset, Color textColour, Action action, Action offAction);

        void draw();
        Action getAction();
        bool isInButton(Vector2 position, bool click);
};
