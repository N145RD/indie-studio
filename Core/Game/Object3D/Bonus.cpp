#include "Bonus.hpp"

Bonus::Bonus(bonus type, Texture2D t0, Texture2D t1, Texture2D t2, Texture2D t3)
{
    _type = type;

    if (type == FIREUP) {
        _texture = t0;
    } else if (type == BOMBUP) {
        _texture = t1;
    } else if (type == SPEEDUP) {
        _texture = t2;
    } else {
        _texture = t3;
    }
    _model = LoadModel("model");
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _hp = 1;
}

Bonus::~Bonus()
{
}

void Bonus::draw()
{
    DrawModel(_model, _position, 1.0f, _color);
}

int Bonus::getType() const
{
    return _type;
}
