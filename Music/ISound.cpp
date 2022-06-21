/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ISound
*/

#include "ISound.hpp"

ISound::ISound(const std::string &file)
{
    _sound = LoadSound(file.c_str());
}

ISound::~ISound()
{
    UnloadSound(_sound);
}

void ISound::playSound()
{
    PlaySound(_sound);
}

void ISound::stopSound()
{
    StopSound(_sound);
}

void ISound::pauseSound()
{
    PauseSound(_sound);
}

void ISound::resumeSound()
{
    ResumeSound(_sound);
}

int ISound::getSoundsPlaying(void)
{
    if (GetSoundsPlaying() != 0)
        return true;
    return false;
}

bool ISound::isSoundPlaying()
{
    return IsSoundPlaying(_sound);
}

void ISound::setSoundVolume(float volume)
{
    SetSoundVolume(_sound, volume);
}
