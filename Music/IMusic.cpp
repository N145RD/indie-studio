/*
** EPITECH PROJECT, 2022
** music
** File description:
** music
*/

#include <iostream>
#include "IMusic.hpp"

IMusic::IMusic(const std::string &file)
{
    _music = LoadMusicStream(file.c_str());
    _initialised = true;
}

IMusic::IMusic()
{
    _initialised = false;
}

IMusic::~IMusic()
{
    if (_initialised)
        UnloadMusicStream(_music);
}

void IMusic::LoadMusic(const std::string &music)
{
    _music = LoadMusicStream(music.c_str());
    _initialised = true;
}

void IMusic::playMusic()
{
    if (_initialised)
        PlayMusicStream(_music);
}

void IMusic::updateMusic()
{
    if (_initialised)
        UpdateMusicStream(_music);
}

void IMusic::pauseMusic()
{
    if (_initialised)
        PauseMusicStream(_music);
}

void IMusic::resumeMusic()
{
    if (_initialised)
        ResumeMusicStream(_music);
}

void IMusic::stopMusic()
{
    if (_initialised)
        StopMusicStream(_music);
}

void IMusic::setMusicVolume(float volume)
{
    if (_initialised)
        SetMusicVolume(_music, volume);
}

void IMusic::setMusicPitch(float pitch)
{
    if (_initialised)
        SetMusicPitch(_music, pitch);
}

bool IMusic::IsMusicStreamPlaying()
{
    return false;
}
