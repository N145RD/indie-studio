#include "Fire.hpp"

Fire::Fire(Model mod, int timer, Texture2D texture, int direction) : _sound("VisualLib/explosion.wav")
{
    _texture = texture;
    _rotation = {0.0, 90.0, 0.0};
    _angle = direction * 90;
    _scale = {1.0, 1.0, 1.0};
    _timer = timer;
    _model = mod;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _counter = 0;
    _hp = 1;
    _color = WHITE;
    _soundPlayed = false;
    _sound.setSoundVolume(0.2f);
}

Fire::~Fire()
{
}

void Fire::animate()
{
    if (!_soundPlayed) {
        _sound.playSound();
        _soundPlayed = true;
    }
    _counter++;
    // if (_animation)
    //     UpdateModelAnimation(_model, _animation[0], _counter);
    if (_counter >= _timer)
        _hp = 0;
    if (!_sound.isSoundPlaying())
        _hp = -1;
}

void Fire::draw()
{
    if (_hp > 0)
        DrawModelEx(_model, _position, _rotation, _angle, _scale, _color);
}
