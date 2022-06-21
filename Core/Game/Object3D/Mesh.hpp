#ifndef MESH_HPP_
#define MESH_HPP_
#include "Model3D.hpp"

class Meshh : public Model3D {
    public:
        Meshh(const std::string&);
        ~Meshh();
        void draw();
        

    protected:
    Mesh med;
    private:
};

#endif /* !MESH_HPP_ */
