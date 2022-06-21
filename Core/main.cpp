/*
** EPITECH PROJECT, 2022
**
** File description:
**
*/

#include <iostream>
#include "SceneManager.hpp"

int main()
{
    InitWindow(1920, 1080, "Bomberman");
    InitAudioDevice();
    SetTargetFPS(60);
    SceneManager manager;
    manager.mainLoop();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
