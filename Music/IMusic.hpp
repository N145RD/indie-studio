/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include "raylib.h"
#include <iostream>

class IMusic
{
public:
    IMusic(const std::string &file);
    IMusic();
    ~IMusic();
    void LoadMusic(const std::string &);
    void playMusic();
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void updateMusic();
    void setMusicVolume(float);
    void setMusicPitch(float);
    bool IsMusicStreamPlaying();

private:
    Music _music;
    bool _initialised;
};

#endif /* !MUSIC_HPP_ */
