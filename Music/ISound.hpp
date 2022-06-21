/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ISound
*/

#ifndef ISOUND_HPP_
#define ISOUND_HPP_

#include "raylib.h"
#include <iostream>

class ISound
{
public:
    ISound(const std::string &file);
    ~ISound();
    void unloadSound();
    void playSound();
    void stopSound();
    void pauseSound();
    void resumeSound();
    int getSoundsPlaying(void);
    bool isSoundPlaying();
    void setSoundVolume(float volume);

private:
    Sound _sound;
};

#endif /* !ISOUND_HPP_ */
