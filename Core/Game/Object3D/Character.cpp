#include "Character.hpp"

using namespace std;

Character::Character(int corner, std::vector<std::shared_ptr<Model3D>> &objs, Map &map, const std::string &texturepath) : _map(map), _objs(objs)
{
    Vector3 pos[4] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 16.0f}, {28.0f, 0.0f, 16.0f}, {28.0f, 0.0f, 0.0f}};
    int mapPos[4][2] = {{0,0}, {0,8}, {14,8}, {14,0}};

    _texture = LoadTexture(texturepath.c_str());
    //_model = LoadModel("VisualLib/KJK.obj");
    _model = LoadModel("VisualLib/Mickey.obj");
    _death = LoadModel("VisualLib/MickeyDeath.iqm");
    _modelB = LoadModel("VisualLib/Bomba.obj");
    _textureB = LoadTexture("VisualLib/red.png");
    _animeCounter = 0;
    _frameAnime = 0;
    _deathCounter = 0;
    _frameDeath = 0;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    SetMaterialTexture(&_death.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _animation = LoadModelAnimations("VisualLib/MickeyAnim.iqm", &_animeCounter);
    _deathAnim = LoadModelAnimations("VisualLib/MickeyDeathAnim.iqm", &_deathCounter);
    _scale = { 3.0f, 3.0f, 3.0f };
    _rotation = {0.0f, 90.f, 00.f};
    _position = pos[corner];
    _x = mapPos[corner][0];
    _y = mapPos[corner][1];
    _angle = 0;
    _fire = 1;
    _maxBomb = 1;
    _bomb = 1;
    _speed = 0.1;
    _wallPass = 0;
    _hp = 1;
    _arma = 0;
    _move = 0;
    _direction = 90;
}

Character::Character(int corner, std::vector<std::shared_ptr<Model3D>> &objs, Map &map) : _map(map), _objs(objs)
{
    Vector3 pos[4] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 16.0f}, {28.0f, 0.0f, 16.0f}, {28.0f, 0.0f, 0.0f}};
    int mapPos[4][2] = {{0,0}, {0,8}, {14,8}, {14,0}};

    _texture = LoadTexture("VisualLib/file8.png");
    //_model = LoadModel("VisualLib/KJK.obj");
    _model = LoadModel("VisualLib/Mickey.obj");
    _death = LoadModel("VisualLib/MickeyDeath.iqm");
    _modelB = LoadModel("VisualLib/Bomba.obj");
    _textureB = LoadTexture("VisualLib/red.png");
    _animeCounter = 0;
    _frameAnime = 0;
    _deathCounter = 0;
    _frameDeath = 0;
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    SetMaterialTexture(&_death.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _animation = LoadModelAnimations("VisualLib/MickeyAnim.iqm", &_animeCounter);
    _deathAnim = LoadModelAnimations("VisualLib/MickeyDeathAnim.iqm", &_deathCounter);
    _scale = { 3.0f, 3.0f, 3.0f };
    _rotation = {0.0f, 90.f, 00.f};
    _position = pos[corner];
    _x = mapPos[corner][0];
    _y = mapPos[corner][1];
    _angle = 0;
    _fire = 1;
    _maxBomb = 1;
    _bomb = 1;
    _speed = 0.1;
    _wallPass = 0;
    _hp = 1;
    _arma = 0;
    _move = 0;
    _direction = 90;
}

Character::~Character()
{
    UnloadModel(_model);
    if (_animation)
        UnloadModelAnimations(_animation, _animeCounter);
    if (_deathAnim)
        UnloadModelAnimations(_deathAnim, _deathCounter);
}

void Character::draw()
{
    if (_hp == 1)
        DrawModelEx(_model, _position, _rotation, _angle, _scale, _color);
    else if (_hp == 0)
        DrawModelEx(_death, _position, _rotation, _angle, _scale, _color);
}

bool Character::checkCollisions(int x, int y, bool wallPass)
{
    switch (_map.getMap(x, y)) {
        case VOID:
        case BONUS:
        case EXPLOSION:
            return true;
        case DESTRUCTIBLE:
            return wallPass;
        default:
            return false;
    }
}

void Character::moveUp()
{
    _angle = 180.0f;
    if (checkCollisions(this->getX(), this->getY() - 1, _wallPass)) {
        if (_move == 0) {
            _move = 0.1;
            _destx = _x;
            _desty = _y - 1;
        }
    }
}

void Character::moveLeft()
{
    _angle = 270.0f;
    if (checkCollisions(this->getX() - 1, this->getY(), _wallPass)) {
        if (_move == 0) {
            _move = 0.1;
            _destx = _x - 1;
            _desty = _y;
        }
    }
}

void Character::moveRight()
{
    _angle = 90.0f;
    if (checkCollisions(this->getX() + 1, this->getY(), _wallPass)) {
        if (_move == 0) {
            _move = 0.1;
            _destx = _x + 1;
            _desty = _y;
        }
    }
}

void Character::moveDown()
{
    _angle = 0.0f;
    if (checkCollisions(this->getX(), this->getY() + 1, _wallPass)) {
        if (_move == 0) {
            _move = 0.1;
            _destx = _x;
            _desty = _y + 1;
        }
    }
}

void Character::drop()
{
    std::cout << "Can put " << _bomb << " bombs down" << std::endl;
    if (_bomb > 0 && _map.getMap(_x, _y) != DESTRUCTIBLE) {
        _bomb--;
        _objs.push_back(std::make_shared<Bomb>(_fire, 240, _arma, _map, _modelB, _textureB));
        _objs.back()->setPosition(_position.x, _position.y, _position.z, _x, _y);
        _map.setMap(_x, _y, BOMB);
        _bombTimes.push_back(120);
    }
}

void Character::reload()
{
}

void Character::powerUp(int x, int y)
{
    std::shared_ptr<Model3D> tmp = _map.getObj(x, y);

    if (!tmp)
        return;
    std::cout << "Player picked up bonus " << tmp->getType() << std::endl;
    if (tmp && tmp->getType() == 0)
        bombUp();
    if (tmp && tmp->getType() == 1)
        fireUp();
    if (tmp && tmp->getType() == 2)
        speedUp();
    if (tmp && tmp->getType() == 3)
        armagedon();
    if (tmp)
        tmp->killed();
}

void Character::fireUp()
{
    _fire++;
}

void Character::bombUp()
{
    _bomb++;
}

void Character::speedUp()
{
    _speed += 0.2;
}

void Character::wallPass()
{
    _wallPass = 1;
}

void Character::armagedon()
{
    _arma = 1;
}

int Character::getFire() const
{
    return _fire;
}

int Character::getBomb() const
{
    return _bomb;
}

int Character::getSpeed() const
{
    return _speed;
}

int Character::getPass() const
{
    return _wallPass;
}

void Character::killed()
{
    _hp = 0;
}
void Character::animate()
{
    for (auto i = _bombTimes.begin(); i != _bombTimes.end(); i++) {
        (*i)--;
        if ((*i) == 0) {
            _bombTimes.erase(i);
            _bomb++;
            break;
        }
    }
    if (_map.getMap(_x, _y) == EXPLOSION)
        _hp = 0;
    if (_hp == 1 && _move != 0) {
        if (_angle == 180.0f)
            _position.z -= _speed * 2;
        if (_angle == 90.0f)
            _position.x += _speed * 2;
        if (_angle == 270.0f)
            _position.x -= _speed * 2;
        if (_angle == 00.0f)
            _position.z += _speed * 2;
        _move += _speed;
    }
    if (_hp == 1 && _move > 0.5) {
        if (_map.getMap(_destx, _desty) == BONUS)
            powerUp(_destx, _desty);
        if (_map.getMap(_x, _y) != BOMB)
            _map.setMap(_x, _y, VOID);
        _x = _destx;
        _y = _desty;
        _map.setMap(_destx, _desty, PLAYER);
    }
    if (_hp == 1 && _move >= 1.0) {
        _position.x = _x * 2;
        _position.z = _y * 2;
        _move = 0;
    }
    if (_animation && _hp == 1 && _move > 0) { // '!' no animation donc pas de warning pour l'instant
        //std::cout << "HERE : " << _frameAnime << " : " << _animation[0].frameCount << " : " << _hp << std::endl;
        _frameAnime++;
        UpdateModelAnimation(_model, _animation[0], _frameAnime);
        if (_frameAnime >= _animation[0].frameCount) {
            _frameAnime = 0;
        }
    }
    if (_deathAnim && _hp == 0) {
        _death.transform = MatrixRotateX(90);
        _frameDeath++;
        UpdateModelAnimation(_death, _deathAnim[0], _frameDeath);
        _scale = {0.03f, 0.03f, 0.03f};
        if (_frameDeath >= _deathAnim[0].frameCount) {
            _frameDeath = 0;
            _hp = -1;
        }
    }
}
