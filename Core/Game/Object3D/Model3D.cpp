#include "Model3D.hpp"

Vector3 Model3D::getPosition() const
{
    return _position;
}

float Model3D::getAngle() const
{
    return _angle;
}

void Model3D::setPosition(float x, float y, float z, int a, int b)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
    _x = a;
    _y = b;
}

void Model3D::setAngle(float radius)
{
    _angle = radius;
}

void Model3D::setRotation(float x, float y, float z)
{
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;
}

int Model3D::getHp() const
{
    return _hp;
}

int Model3D::getX() const
{
    return _x;
}

int Model3D::getY() const
{
    return _y;
}

int Model3D::getType() const
{
    return 4;
}

void Model3D::killed()
{
    _hp = -1;
}

void Model3D::animate()
{
    // _counter++;
    // if (_animation) {
    //     UpdateModelAnimation(_model, _animation[0], _counter);
    //     if (_counter >= _animation[0].frameCount)
    //         _counter = 0;
    // }
}

void Model3D::draw()
{
    DrawModelEx(_model, _position, _rotation, _angle, _scale, _color);
}
