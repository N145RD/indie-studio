#pragma once

#include "Model3D.hpp"

enum bonus {
    BOMBUP,
    FIREUP,
    SPEEDUP,
    ARMAGEDON,
    WALLPASS
};

class Bonus : public Model3D {
    public:
        Bonus(bonus, Texture2D, Texture2D, Texture2D, Texture2D);
        ~Bonus();

        int getType() const;
        void draw();
    protected:
    private:
        bonus _type;
};
