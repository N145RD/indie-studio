#include "BlockI.hpp"

BlockI::BlockI(Model mod, Texture2D texture)
{
    // _texture = LoadTexture("VisualLib/pngwing.png");
    // _model = LoadModel("VisualLib/crate.obj");
    _texture = texture;
    _model = mod;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    // _counter = 0;
    // _animation = LoadModelAnimations("modelAnimation", &_counter);
    _hp = 1;
}

BlockI::~BlockI()
{
    //UnloadModel(_model);
//     if (_animation)
//         UnloadModelAnimations(_animation, _counter);
}

void BlockI::draw()
{
    DrawModel(_model, _position, 1.0f, _color);
}
