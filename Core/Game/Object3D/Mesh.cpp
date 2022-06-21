#include "Mesh.hpp"

Meshh::Meshh(const std::string& texture)
{
    _texture = LoadTexture(texture.c_str());
    _position = (Vector3){13, 0, 10};
    med = GenMeshPlane(55, 35, 5, 5);
    _model = LoadModelFromMesh(med);
    _x = -15;
    _y = -15;
    _hp = 20;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

void Meshh::draw()
{
    DrawModel(_model, _position, 1.0f, _color);
}

Meshh::~Meshh()
{
}
