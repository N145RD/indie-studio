#pragma once
#include <vector>
#include "Scene.hpp"

class SceneManager {
    std::map<int, std::shared_ptr<Scene>> _scenes;
    int _currentScene;
    float _up;
    public:
        SceneManager();

        void changeScene(SceneType type);
        void drawScene();
        Action updateSceneFromEvent(const Event &event);
        Action updateSceneFromFrame();
        void mainLoop();
};
