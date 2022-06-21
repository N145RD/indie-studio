/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#include "Scene.hpp"
//#include "../Menu/ButtonEvent.hpp"

Scene::Scene(SceneType type) : _3dAssets(), _2dAssets(), _map(_3dAssets), _camera() //, _music()
{
    _type = type;
    switch (type)
    {
    case SplashScreen:
        _music.LoadMusic("VisualLib/splashscreenbomberman.wav");
        _2dAssets.push_back(std::make_shared<Sprite>("VisualLib/splashscreen.png", (Vector2){0, 0}));
        _buttons.push_back(std::make_shared<Button>("PRESS TO PLAY", (Vector2){875, 980}, (Vector2){8, 12}, WHITE, _main_menu));
        break;
    case MainMenu:
        _music.LoadMusic("VisualLib/bombermanMusic.wav");
        _2dAssets.push_back(std::make_shared<Sprite>("VisualLib/menu_game.png", (Vector2){0, 0}, GRAY));
        _buttons.push_back(std::make_shared<Button>("PLAY", (Vector2){875, 300}, (Vector2){15, 10}, WHITE, _pregame));
        _buttons.push_back(std::make_shared<Button>("OPTIONS", (Vector2){875, 600}, (Vector2){15, 10}, WHITE, _options));
        _buttons.push_back(std::make_shared<Button>("QUIT", (Vector2){875, 900}, (Vector2){15, 10}, WHITE, _exit));
        break;
    case Options:
        _music.LoadMusic("VisualLib/bombermanMusic.wav");
        _music.setMusicPitch(0.9);
        _2dAssets.push_back(std::make_shared<Sprite>("VisualLib/option_game.png", (Vector2){0, 0}, GRAY));
        _buttons.push_back(std::make_shared<CheckBox>("SOUND ON/OFF", (Vector2){875, 300}, (Vector2){40, 9}, WHITE, _vol_on, _vol_off));
        _buttons.push_back(std::make_shared<Button>("Volume Up", (Vector2){600, 500}, (Vector2){15, 10}, WHITE, _vol_up));
        _buttons.push_back(std::make_shared<Button>("Volume Down", (Vector2){1150, 500}, (Vector2){15, 10}, WHITE, _vol_down));
        _buttons.push_back(std::make_shared<Button>("BACK", (Vector2){875, 900}, (Vector2){15, 10}, WHITE, _main_menu));
        _music.pauseMusic();
        break;
    case PreGame:
        _music.LoadMusic("VisualLib/choosegame.wav");
        _2dAssets.push_back(std::make_shared<Sprite>("VisualLib/menu.png", (Vector2){0, 0}, GRAY));
        _buttons.push_back(std::make_shared<Button>("LOCAL GAME", (Vector2){875, 300}, (Vector2){15, 10}, WHITE, _game));
        _buttons.push_back(std::make_shared<Button>("BACK", (Vector2){875, 900}, (Vector2){15, 10}, WHITE, _main_menu));
        _buttons.push_back(std::make_shared<Button>("SOLO GAME", (Vector2){875, 600}, (Vector2){15, 10}, WHITE, _game_ia));
        break;
    case Game:
    case GameIA:
        _music.LoadMusic("VisualLib/ingame.wav");
        _3dAssets.push_back(std::make_shared<Meshh>("VisualLib/plage.png"));
        _map.generateWalls(20);
        _camera = {(Vector3){13, 19, 10}, (Vector3){13, -35, 9.9}, (Vector3){0, 1, 0}, (float)75.0, (int)CAMERA_PERSPECTIVE};
        _players.push_back(std::make_shared<Character>(0, _3dAssets, _map));
        if (type == Game)
        {
            _players.push_back(std::make_shared<Character>(2, _3dAssets, _map));
        }
        else
        {
            _IAs.push_back(std::make_shared<IA>(1, _3dAssets, _map));
            _IAs.push_back(std::make_shared<IA>(2, _3dAssets, _map));
            _IAs.push_back(std::make_shared<IA>(3, _3dAssets, _map));
        }
        break;
    case Score:
        _music.LoadMusic("VisualLib/A Very Brady Special.mp3");
        _2dAssets.push_back(std::make_shared<Sprite>("VisualLib/splashscreen.png", (Vector2){0, 0}, GRAY));
        _buttons.push_back(std::make_shared<Button>("PLAY AGAIN", (Vector2){875, 300}, (Vector2){15, 10}, WHITE, _pregame));
        _buttons.push_back(std::make_shared<Button>("BACK TO MENU", (Vector2){875, 600}, (Vector2){15, 10}, WHITE, _main_menu));
        break;
    case Pause:
        _music.LoadMusic("VisualLib/bombermanMusic.wav");
        _buttons.push_back(std::make_shared<Button>("RESUME", (Vector2){875, 300}, (Vector2){15, 10}, WHITE, _game));
        _buttons.push_back(std::make_shared<Button>("BACK TO MENU", (Vector2){875, 600}, (Vector2){15, 10}, WHITE, _main_menu));
        break;
    }
}

void Scene::draw() const
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (_type == Game || _type == GameIA)
    {
        BeginMode3D(_camera);
        for (auto model : _3dAssets)
        {
            if (model)
            {
                model->draw();
                model->animate();
            }
        }
        for (auto model : _players)
        {
            if (model)
            {
                model->draw();
                model->animate();
            }
        }
        for (auto model : _IAs)
        {
            if (model)
            {
                model->draw();
                model->animate();
            }
        }
        for (auto model : _2dAssets)
        {
            if (model)
                model->draw();
        }
        EndMode3D();
    }
    else
    {
        for (auto model : _2dAssets)
        {
            if (model)
                model->draw();
        }
        for (auto button : _buttons)
        {
            if (button)
                button->draw();
        }
    }
    EndDrawing();
}

Action Scene::updateSceneFromEvent(const Event &event)
{
    if (_type == Game || _type == GameIA)
        return updateSceneFromEventGame(event);
    return updateSceneFromEventMenus(event);
}

Action Scene::updateSceneFromEventGame(const Event &event)
{
    constexpr int keys[2][5] = {{87, 65, 83, 68, 32}, {265, 263, 264, 262, 257}};
    if (event.isKeyBoard())
    {
        for (int i = 0; i < _players.size(); i++)
        {
            if (_players.at(i))
            {
                if (event.getKey() == keys[i][0])
                    _players[i]->moveUp();
                if (event.getKey() == keys[i][1])
                    _players[i]->moveLeft();
                if (event.getKey() == keys[i][2])
                    _players[i]->moveDown();
                if (event.getKey() == keys[i][3])
                    _players[i]->moveRight();
                if (event.getKey() == keys[i][4])
                    _players[i]->drop();
            }
        }
    }
    return _nothing;
}

Action Scene::updateSceneFromEventMenus(const Event &event)
{
    Action tmp = _nothing;

    if (_type == SplashScreen && event.isKeyBoard())
        return _main_menu;
    for (auto button : _buttons)
    {
        if (!button)
            continue;
        if (button->isInButton(event.getMousePos(), event.isMousePressed()))
        {
            if (event.isMouseReleased())
            {
                button->playSound();
                tmp = button->getAction();
            }
        }
    }
    return tmp;
}

Action Scene::updateSceneFromFrame()
{
    int stillAlive = 0;
    int playersAlive = 0;

    _music.updateMusic();
    if (_type == Game || _type == GameIA)
    {
        std::cout << _map;
        for (auto i = _3dAssets.begin(); i != _3dAssets.end(); i++)
        {
            if (*i)
            {
                (*i)->animate();
                if (_map.getMap((*i)->getX(), (*i)->getY()) == EXPLOSION)
                {
                    for (auto player : _players)
                    {
                        if (player)
                        {
                            if ((*i)->getX() == player->getX() && (*i)->getY() == player->getY())
                            {
                                player->killed();
                            }
                        }
                    }
                    for (auto ia : _IAs)
                    {
                        if (ia)
                        {
                            if ((*i)->getX() == ia->getX() && (*i)->getY() == ia->getY())
                            {
                                ia->killed();
                            }
                        }
                    }
                }
                if ((*i)->getHp() <= -1)
                {
                    if (_map.getMap((*i)->getX(), (*i)->getY()) == EXPLOSION)
                        _map.setMap((*i)->getX(), (*i)->getY(), VOID);
                    _3dAssets.erase(i--);
                }
            }
        }
        for (auto player : _players)
        {
            if (player)
            {
                if (player->getHp() >= 0)
                {
                    stillAlive++;
                    playersAlive++;
                }
            }
        }
        for (auto ia : _IAs)
        {
            if (ia)
            {
                if ((ia)->getHp() >= 0)
                    stillAlive++;
            }
        }
        for (auto ia : _IAs)
        {
            if (ia)
            {
                ia->progress();
            }
        }
        if (_type == Game && stillAlive <= 1)
            return _score;
        if (_type == GameIA && (playersAlive <= 0 || stillAlive <= 1))
            return _score;
    }
    return _nothing;
}

void Scene::stopMusic()
{
    _music.pauseMusic();
}

void Scene::startMusic()
{
    _music.playMusic();
}
