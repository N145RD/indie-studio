#include "CheckBox.hpp"

CheckBox::CheckBox(const std::string &text, Vector2 position, Vector2 textOffset, Color textColour, Action action, Action offAction) : Button(text, "VisualLib/Spritesheet/redSheet.png", "VisualLib/buttonfx.wav", position, textOffset, textColour, action, {380, 0, 38, 36}, {380, 0, 38, 36}, {380, 36, 38, 36})
{
    _status = true;
    _offAction = offAction;
}

void CheckBox::draw()
{
    if (_status)
        _texture.drawRec(_normal, (Vector2){_buttonPosition.x, _buttonPosition.y});
    else
        _texture.drawRec(_clicked, (Vector2){_buttonPosition.x, _buttonPosition.y});
    DrawText(_text.c_str(), _buttonPosition.x + _textOffset.x, _buttonPosition.y + _textOffset.y, 20, _textColour);
}

Action CheckBox::getAction()
{
    _status = !_status;
    if (_status)
        return _action;
    else
        return _offAction;
}

bool CheckBox::isInButton(Vector2 position, bool click)
{
    _lastRequestedPos = position;
    if (_buttonPosition.x < position.x && _buttonPosition.x + _buttonPosition.width > position.x
     && _buttonPosition.y < position.y && _buttonPosition.y + _buttonPosition.height > position.y) {
        return true;
    }
    _soundHasPlayed = false;
    return false;
}
