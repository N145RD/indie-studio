#pragma once

#include "Model3D.hpp"

class BlockD : public Model3D {
    public:
        BlockD(Model, Texture2D);
        ~BlockD();

        void draw();
    protected:
    private:
};

