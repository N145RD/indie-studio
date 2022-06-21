/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Texture.hpp
*/

#include "Model2D.hpp"

class Sprite : public Model2D {
    public:
        Sprite(const std::string&, Vector2 position);
        Sprite(const std::string&, Vector2 position, Color colour);
        ~Sprite();

        Vector2 getPosition() const;

        void setPosition(float, float);
        Texture2D getTexture() const;

        void drawRec(Rectangle, Vector2);

    protected:

    private:
};
