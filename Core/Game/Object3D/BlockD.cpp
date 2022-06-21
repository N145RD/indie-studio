#include "BlockD.hpp"

BlockD::BlockD(Model mod, Texture2D texture)
{
    // _texture = LoadTexture("VisualLib/hacker.png");
    // _model = LoadModel("VisualLib/crate.obj");
    _texture = texture;
    _model = mod;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    //_counter = 0;
    // _animation = LoadModelAnimations("", &_counter);
    _hp = 1;
}

BlockD::~BlockD()
{
    //UnloadModel(_model);
    // if (_animation)
    //     UnloadModelAnimations(_animation, _counter);
}

void BlockD::draw()
{
    DrawModel(_model, _position, 1.0f, _color);
}
