#include "IA.hpp"

IA::IA(int corner, std::vector<std::shared_ptr<Model3D>> &objs, Map &map) : Character(corner, objs, map, "VisualLib/robot.png")
{
    _currentDestination = std::make_pair(_x, _y);
}

void IA::progress()
{
    loopMove();
}

void IA::loopMove()
{
  if (_map.getMap(_x + 1, _y) == UNBREAKABLE || _map.getMap(_x + 1, _y) == DESTRUCTIBLE) { //si vers la droite il y a une case alors move en bas
        _speed = 0.02;
        moveDown();
    } // bonnes dir?

    if (_map.getMap(_x, _y + 1) == UNBREAKABLE || _map.getMap(_x , _y + 1) == DESTRUCTIBLE) { //si vers le bas il y a une case alors move a gauche
        _speed = 0.02;
        moveLeft();
    }

    if (_map.getMap(_x - 1, _y) == UNBREAKABLE || _map.getMap(_x - 1, _y) == DESTRUCTIBLE) { //si vers la gauche il ya une case alors move a droite
        _speed = 0.02;
        moveUp();
    }

    if (_map.getMap(_x, _y - 1) == UNBREAKABLE || _map.getMap(_x, _y - 1) == DESTRUCTIBLE) { //si vers le haut il y a une case alors move a droite
        _speed = 0.02;
        moveRight();
    }
}

void IA::bombEscape()
{
    if (_map.getMap(_x, _y) == BOMB) {
        if (_map.getMap(_x + 1, _y) && _map.getMap(_x + 2, _y) == VOID) {
            moveRight();
            moveRight();
        }
        if (_map.getMap(_x - 1, _y) && _map.getMap(_x - 2, _y) == VOID) {
            moveLeft();
            moveLeft();
        }
        if (_map.getMap(_x, _y + 1) && _map.getMap(_x, _y + 2) == VOID) {
            moveDown();
            moveDown();
        }
        if (_map.getMap(_x, _y - 1) && _map.getMap(_x, _y - 2) == VOID) {
            moveUp();
            moveUp();
        }
    }
}
