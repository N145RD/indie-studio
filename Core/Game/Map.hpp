/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <memory>
#include "Object3D/Model3D.hpp"
#include "Object3D/BlockI.hpp"
#include "Object3D/BlockD.hpp"
#include "Object3D/Bonus.hpp"
#include "Object3D/Fire.hpp"
#include <chrono>

enum TypeOnMap {
    VOID,
    DESTRUCTIBLE,
    UNBREAKABLE,
    BOMB,
    EXPLOSION,
    PLAYER,
    BONUS
};
// load model unique
class Map {
    public:
        Map(std::vector<std::shared_ptr<Model3D>> &objs);
        ~Map();

        void setMap(int, int, TypeOnMap);
        TypeOnMap getMap(int, int) const;

        std::shared_ptr<Model3D> getObj(int, int);

        void explosion(int, int, int, int); // x, y, power, arma
        void generateWalls(int BlockDensity);
        void spawnBonus(int, int, Vector3);
        void explosed(int, int, int , int);
        int getWidth() const;
        int getHeight() const;
    private:
        // std::vector<BlockD> _destructible;
        // std::vector<BlockI> _unbreakable;
        Model _modelI;
        Model _modelD;
        Model _fireCross;
        Model _fireTube;
        Model _fireEdge;
        Texture2D _textureI;
        Texture2D _textureD;
        Texture2D _texture0;
        Texture2D _texture1;
        Texture2D _texture2;
        Texture2D _texture3;
        Texture2D _texture4;
        std::vector<std::shared_ptr<Model3D>> &_objs;
        std::map<int, std::map<int, TypeOnMap>> _map;
        std::map<int, std::map<int, Vector3>> _pos;
        bool _inited;
        int _width;
        int _height;
};

std::ostream &operator<<(std::ostream &output, const TypeOnMap &type);
std::ostream &operator<<(std::ostream &output, const Map &map);
