#pragma once

#include <iostream>
#include "Model3D.hpp"
#include "../Map.hpp"
#include "Bomb.hpp"

class Character : public Model3D {
    public:
        Character(int, std::vector<std::shared_ptr<Model3D>> &, Map &); // int = position de depart
        Character(int, std::vector<std::shared_ptr<Model3D>> &, Map &, const std::string &); // int = position de depart
        ~Character();
// aimantation
        void moveLeft();
        void moveUp();
        void moveRight();
        void moveDown();
//
        void drop(); // pose bomb
        void reload(); // recharge nb bomb

        void powerUp(int, int); // use bonus
        void fireUp(); // boost puissance de la bomb
        void bombUp(); // boost nb bomb
        void speedUp(); // boost speed
        void wallPass(); // boost wallpass
        void armagedon(); // armageddon

        int getFire() const; // puissance de la bomb
        int getBomb() const; // nb bomb restante
        int getSpeed() const; // speed
        int getPass() const; // wallpass
        int getArma() const; // arma : 0 = no | 1 = oui

        void killed();
        void draw();
        void animate();
        bool checkCollisions(int x, int y, bool wallPass);
    protected:
        Model _modelB;
        Texture2D _textureB;
        Model _death;
        ModelAnimation *_deathAnim;
        unsigned int _deathCounter;
        int _bomb; // bomb restante
        int _maxBomb; // nb max de bomb
        int _fire; // puissance de la bomb
        float _speed; // vitesse du perso
        int _arma;
        int _wallPass; // 0 passe pas; 1 passe
        std::vector<std::shared_ptr<Model3D>> &_objs; // vecteur d'objet pour la construction de la bombe
        std::vector<int> _bombTimes;
        // std::vector<Character*> &_player; // vecteur des joueurs pour l'explosionde la bomb
        // std::vector<Character*> &_ia; // vecteur des ia pour l'explosion de la bombe
        Map &_map; // map pour gestion de la bombe et bonus
        float _move;
        int _direction;
        int _destx;
        int _desty;
    private:
};
