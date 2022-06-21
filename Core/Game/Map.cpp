/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#include "Map.hpp"

void Map::generateWalls(int BlockDensity)
{
    std::minstd_rand0 rand(std::chrono::system_clock::now().time_since_epoch().count());
    _textureI = LoadTexture("VisualLib/blue.png");
    _modelI = LoadModel("VisualLib/crate.obj");
    _textureD = LoadTexture("VisualLib/green.png");
    _modelD = LoadModel("VisualLib/crate.obj");
    _texture0 = LoadTexture("VisualLib/fire.png"); // fire up
    _texture1 = LoadTexture("VisualLib/bomb_up.png"); // bomb up
    _texture2 = LoadTexture("VisualLib/speed.png"); //speed up
    _texture3 = LoadTexture("VisualLib/armagedon.png"); // arma
    _texture4 = LoadTexture("VisualLib/red.png"); // deflagration
    _fireCross = LoadModel("VisualLib/cross.obj");
    _fireTube = LoadModel("VisualLib/tube.obj");
    _fireEdge = LoadModel("VisualLib/edge.obj");
    Vector3 pos;

    for (int i = -1; i < _width + 1; i++) {
        _map[i][-1] = UNBREAKABLE;
        _objs.push_back(std::make_shared<BlockI>(_modelI, _textureI));
        _objs.back()->setPosition(i * 2, 0, -1 * 2, i, -1);
        _map[i][_height] = UNBREAKABLE;
        _objs.push_back(std::make_shared<BlockI>(_modelI, _textureI));
        _objs.back()->setPosition(i * 2, 0, _height * 2, i, _height);
    }
    for (int i = -1; i < _height + 1; i++) {
        _map[-1][i] = UNBREAKABLE;
        _objs.push_back(std::make_shared<BlockI>(_modelI, _textureI));
        _objs.back()->setPosition(-1 * 2, 0, i * 2, -1, i);
        _map[_width][i] = UNBREAKABLE;
        _objs.push_back(std::make_shared<BlockI>(_modelI, _textureI));
        _objs.back()->setPosition(_width * 2, 0, i * 2, _width, i);
    }
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                _map[i][j] = UNBREAKABLE;
                _objs.push_back(std::make_shared<BlockI>(_modelI, _textureI));
                _objs.back()->setPosition(i * 2, 0, j * 2, i, j);
            } else if ((i <= 1 || i >= _width - 2) && (j <= 1 || j >= _height - 2)) {
                _map[i][j] = VOID;
                pos = {.x = i * 2.0f, .y = 0.0f, .z = j * 2.0f};
                _pos[i][j] = pos;
            } else {
                if (rand() % 100  > BlockDensity) {
                    _map[i][j] = DESTRUCTIBLE;
                    _objs.push_back(std::make_shared<BlockD>(_modelD, _textureD));
                    _objs.back()->setPosition(i * 2, 0, j * 2, i, j);
                    pos = {.x = i * 2.0f, .y = 0.0f, .z = j * 2.0f};
                    _pos[i][j] = pos;
                } else {
                    pos = {.x = i * 2.0f, .y = 0.0f, .z = j * 2.0f};
                    _pos[i][j] = pos;
                    _map[i][j] = VOID;
                }
            }
        }
    }
    _inited = true;
}

Map::~Map()
{
    if (_inited) {
        UnloadModel(_modelI);
        UnloadModel(_modelD);
    }
}

Map::Map(std::vector<std::shared_ptr<Model3D>> &objs) : _objs(std::ref(objs))
{
    _width = 15;
    _height = 9;
    _inited = false;
}

int Map::getWidth() const
{
    return _width;
}

int Map::getHeight() const
{
    return _height;
}

void Map::setMap(int x, int y, TypeOnMap value)
{
    _map[x][y] = value;
}

TypeOnMap Map::getMap(int x, int y) const
{
    try {
        return _map.at(x).at(y);
    } catch (...) {
        return UNBREAKABLE;
    }
}

std::shared_ptr<Model3D> Map::getObj(int x, int y)
{
    std::shared_ptr<Model3D> item = nullptr;
    int finds = 0;

    for (auto it = _objs.begin(); it != _objs.end(); it++) {
        if ((*it)) {
            if ((*it)->getX() == x && (*it)->getY() == y) {
                item = (*it);
                finds++;
            }
        }
    }
    std::cout << "Found " << finds << " items at coords " << x << "," << y << std::endl;
    return item;
}

void Map::spawnBonus(int x, int y, Vector3 pos)
{
    std::minstd_rand0 rand(std::chrono::system_clock::now().time_since_epoch().count());
    int type = rand() % 4;

    if (rand() % 100 > 80) {
        _objs.push_back(std::make_shared<Bonus>((bonus)type, _texture0, _texture1, _texture2, _texture3));
        _objs.back()->setPosition(pos.x, pos.y, pos.z, x, y);
        _map[x][y] = BONUS;
     } else
        _map[x][y] = VOID;
}

void Map::explosed(int x, int y, int bit, int direction)
{
    switch (bit) {
        case 0:
            _objs.push_back(std::make_shared<Fire>(_fireCross, 40, _texture4, direction));
            break;
        case 1:
            _objs.push_back(std::make_shared<Fire>(_fireTube, 40, _texture4, direction));
            break;
        case 2:
            _objs.push_back(std::make_shared<Fire>(_fireEdge, 40, _texture4, direction));
            break;
        default:
            _objs.push_back(std::make_shared<Fire>(_fireCross, 40, _texture4, direction));
    }
    _objs.back()->setPosition(_pos[x][y].x, _pos[x][y].y, _pos[x][y].z, x, y);
    if (_map[x][y] != DESTRUCTIBLE) 
        _map[x][y] = EXPLOSION;
}

void Map::explosion(int x, int y, int fire, int arma)
{
    std::shared_ptr<Model3D> tmp = nullptr;

    explosed(x, y, 0, 0);
    for (int i = 1; i <= fire && _map[x - i][y] != UNBREAKABLE; i++) {
        tmp = getObj(x - i, y);
        explosed(x - i, y, (i == fire ? 2 : 1), 1);
        if (tmp && _map[x - i][y] == DESTRUCTIBLE && arma == 1) {
            spawnBonus(x - i, y, tmp->getPosition());
        } else if (tmp && _map[x - i][y] == DESTRUCTIBLE && arma == 0) {
            spawnBonus(x - i, y, tmp->getPosition());
            i = fire + 100;
        }
        if (tmp)
            tmp->killed();
    }
    for (int i = 1; i <= fire && _map[x + i][y] != UNBREAKABLE; i++) {
        tmp = getObj(x + i, y);
        explosed(x + i, y, (i == fire ? 2 : 1), 3);
        if (tmp && _map[x + i][y] == DESTRUCTIBLE && arma == 1) {
            spawnBonus(x + i, y, tmp->getPosition());
        } else if (tmp && _map[x + i][y] == DESTRUCTIBLE && arma == 0) {
            spawnBonus(x + i, y, tmp->getPosition());
            i = fire + 100;
        }
        if (tmp)
            tmp->killed();
    }
    for (int i = 1; i <= fire && _map[x][y - i] != UNBREAKABLE; i++) {
        tmp = getObj(x, y - i);
        explosed(x, y - i, (i == fire ? 2 : 1), 0);
        if (tmp && _map[x][y - i] == DESTRUCTIBLE && arma == 1) {
            spawnBonus(x, y - i, tmp->getPosition());
        } else if (tmp && _map[x][y - i] == DESTRUCTIBLE && arma == 0) {
            spawnBonus(x, y - i, tmp->getPosition());
            i = fire + 100;
        }
        if (tmp)
            tmp->killed();
    }
    for (int i = 1; i <= fire && _map[x][y + i] != UNBREAKABLE; i++) {
        tmp = getObj(x, y + i);
        explosed(x, y + i, (i == fire ? 2 : 1), 2);
        if (tmp && _map[x][y + i] == DESTRUCTIBLE && arma == 1) {
            spawnBonus(x, y + i, tmp->getPosition());
        } else if (tmp && _map[x][y + i] == DESTRUCTIBLE && arma == 0) {
            spawnBonus(x, y + i, tmp->getPosition());
            i = fire + 100;
        }
        if (tmp)
            tmp->killed();
    }
}

std::ostream &operator<<(std::ostream &output, const TypeOnMap &type)
{
    switch (type) {
        case VOID:
            output << "VOID";
            break;
        case DESTRUCTIBLE:
            output << "DEST";
            break;
        case UNBREAKABLE:
            output << "UNBR";
            break;
        case BOMB:
            output << "BOMB";
            break;
        case EXPLOSION:
            output << "FIRE";
            break;
        case PLAYER:
            output << "PLAY";
            break;
        case BONUS:
            output << "BONI";
            break;
    }
    return output;
}

std::ostream &operator<<(std::ostream &output, const Map &map)
{
    output << "Map : " << map.getHeight() << " by " << map.getWidth() << std::endl;
    for (int i = 0; i < map.getHeight(); i++) {
        for (int j = 0; j < map.getWidth(); j++) {
            output << map.getMap(j, i);
            if (j != map.getWidth() - 1)
                output << " | ";
        }
        output << std::endl;
    }
    return output;
}
