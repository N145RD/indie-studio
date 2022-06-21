#include "Model2D.hpp"

void Model2D::draw()
{
    DrawTexture(_texture, _position.x, _position.y, _color);
}
