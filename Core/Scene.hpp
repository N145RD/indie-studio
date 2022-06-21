/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#pragma once
#include <vector>
#include "../Music/IMusic.hpp"
#include "Menu/Button.hpp"
#include "Menu/CheckBox.hpp"
#include "Event.hpp"
#include "Game/Object3D/Character.hpp"
#include "Game/Object3D/IA.hpp"
#include "Game/Map.hpp"
#include "Game/Object3D/Mesh.hpp"

enum SceneType {
    SplashScreen,
    MainMenu,
    Options,
    PreGame,
    Game,
    GameIA,
    Score,
    Pause
};

class Scene {
    std::vector<std::shared_ptr<Model3D>> _3dAssets;
    std::vector<std::shared_ptr<Model2D>> _2dAssets;
    std::vector<std::shared_ptr<Button>> _buttons;
    SceneType _type;
    std::vector<std::shared_ptr<Character>> _players;
    std::vector<std::shared_ptr<IA>> _IAs;
    Map _map;
    Camera _camera;
    IMusic _music;
    public :
        Scene(SceneType type);

        void draw() const;
        Action updateSceneFromEvent(const Event &event);
        Action updateSceneFromEventMenus(const Event &event);
        Action updateSceneFromEventGame(const Event &event);
        Action updateSceneFromFrame();
        void startMusic();
        void stopMusic();
};
