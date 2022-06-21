#pragma once

#include "Model3D.hpp"

class Fire : public Model3D {
    int _timer;
    int _counter;
    ISound _sound;
    bool _soundPlayed;
    public:
        Fire(Model, int, Texture2D, int); // timer, model, place
        ~Fire();

        void animate();
        void draw();
};
