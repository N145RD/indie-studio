#pragma once

#include "Character.hpp"

class IA : public Character {
    public:
        IA(int, std::vector<std::shared_ptr<Model3D>> &, Map &); // int = position de depart

        void progress();
        void bombEscape();
        void loopMove();
    protected:
        std::pair<int, int> _currentDestination;
};
