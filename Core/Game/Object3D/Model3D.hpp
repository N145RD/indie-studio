#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "../../../Music/ISound.hpp"

class Model3D {
    public:
        virtual ~Model3D() = default;

        void setPosition(float, float, float, int, int);
        void setAngle(float);
        void setRotation(float, float, float);

        Vector3 getPosition() const;
        float getAngle() const;
        int getHp() const;
        int getX() const;
        int getY() const;
        virtual int getType() const;

        virtual void killed();

        virtual void animate();
        virtual void draw();
    protected:
        Model _model;
        unsigned int _animeCounter;
        Vector3 _position;
        Vector3 _scale;
        Vector3 _rotation;
        ModelAnimation *_animation;
        int _frameAnime;
        int _frameDeath;
        Color _color = WHITE;
        Texture2D _texture;
        float _angle;
        int _x;
        int _y;
        int _hp;
        int _type;
    private:
};
