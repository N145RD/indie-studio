#include "Bomb.hpp"

Bomb::Bomb(int power, int timer, int arma, Map &map, Model model, Texture2D texture) : _map(map)
{
    _texture = texture;
    _model = model;
    // _texture = texture;
    // _model = model;
    _timer = timer;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _counter = 0;
    //_animation = LoadModelAnimations("modelAnimation", &_counter);
    _power = power;
    _hp = 1;
    _state = 0;
    _arma = arma;
}

Bomb::~Bomb()
{
    //UnloadModel(_model);
    // if (_animation)
    //     UnloadModelAnimations(_animation, _counter);
}

int Bomb::getPower() const
{
    return _power;
}

int Bomb::getArma() const
{
    return _arma;
}

void Bomb::killed()
{
    if (_state)
        _hp = -1;
    else {
        _state = 1;
        _map.explosion(_x, _y, _power, _arma);
        _map.setMap(_x, _y, VOID);
        _hp = -1;
    }
}

void Bomb::animate()
{
    _counter++;
    // if (_animation)
    //     UpdateModelAnimation(_model, _animation[0], _counter);
    if (_counter >= _timer && _state == 0) {
        _map.explosion(_x, _y, _power, _arma);
        std::cout << "Exploding at coords " << _x << "," << _y << std::endl;
        _state = 1;
        killed();
        _map.setMap(_x, _y, EXPLOSION);
    }
}

void Bomb::draw()
{
    DrawModel(_model, _position, 0.5f, _color);
}
