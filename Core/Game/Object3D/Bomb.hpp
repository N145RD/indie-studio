#pragma once

#include "Model3D.hpp"
#include "../Map.hpp"

class Bomb : public Model3D {
    public:
        Bomb(int, int, int, Map &, Model, Texture2D); // int = power
        ~Bomb();

        int getPower() const; // puissance de la bombe
        int getArma() const; // arma 0 / 1;
///
        void animate(); // a voir pour animation
///
        void killed();
        void draw();
    protected:
    private:
        int _power; // puissance de la bombe
        int _timer;
        int _state;
        int _arma;
        int _counter;
        Map &_map;
};
