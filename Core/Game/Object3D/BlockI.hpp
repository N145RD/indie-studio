#pragma once

#include "Model3D.hpp"

class BlockI : public Model3D {
    public:
        BlockI(Model, Texture2D);
        ~BlockI();

        void draw();
    protected:
    private:
};
