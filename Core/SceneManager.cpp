#include "SceneManager.hpp"

SceneManager::SceneManager()
{
    _scenes[0] = std::make_shared<Scene>(SplashScreen);
    _currentScene = 0;
    _scenes[_currentScene]->startMusic();
    _up = 100;
}

void SceneManager::changeScene(SceneType destination)
{
    if ((destination == Game || destination == GameIA) && _scenes.find(destination) != _scenes.end()) {
        _scenes.erase(_scenes.find(destination));
    }
    if (_scenes.find(destination) != _scenes.end()) {
        _currentScene = destination;
    } else {
        _scenes[destination] = std::make_shared<Scene>(destination);
        _scenes[_currentScene]->stopMusic();
        _currentScene = destination;
        _scenes[_currentScene]->startMusic();
    }
}

void SceneManager::drawScene()
{
    _scenes[_currentScene]->draw();
}

Action SceneManager::updateSceneFromEvent(const Event &event)
{
    Action tmp = _scenes[_currentScene]->updateSceneFromEvent(event);

    switch (tmp) {
        case (_main_menu):
            changeScene(MainMenu);
            return _nothing;
        case (_options):
            changeScene(Options);
            return _nothing;
        case (_pregame):
            changeScene(PreGame);
            return _nothing;
        case (_pause):
            changeScene(Pause);
            return _nothing;
        case (_game):
            changeScene(Game);
            return _nothing;
        case (_game_ia):
            changeScene(GameIA);
            return _nothing;
        case (_score):
            changeScene(Score);
            return _nothing;
        case (_vol_up):
            _up = (_up >= 1.0 ? 1.0 : _up + 0.1);
            SetMasterVolume(_up);
            return _nothing;
        case (_vol_down):
            _up = (_up <= 0 ? 0 : _up - 0.1);
            SetMasterVolume(_up);
            return _nothing;
        case (_vol_off):
            SetMasterVolume(0.0);
            return _nothing;
        case (_vol_on):
            SetMasterVolume(_up);
            return _nothing;
        case (_music_up):
            return _nothing;
        case (_music_down):
            return _nothing;
        default:
            return tmp;
    };
}

Action SceneManager::updateSceneFromFrame()
{
    Action tmp = _scenes[_currentScene]->updateSceneFromFrame();

    switch (tmp) {
        case (_score):
            changeScene(Score);
            return _nothing;
        default:
            return tmp;
    }
}

void SceneManager::mainLoop()
{
    while (GetKeyPressed() != 0) {}
    while (!WindowShouldClose()) {
        drawScene();
        if (updateSceneFromEvent(Event()) == _exit)
            break;
        if (updateSceneFromFrame() == _exit)
            break;
    }
}
