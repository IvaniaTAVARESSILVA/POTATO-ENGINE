#pragma once
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "miniaudio/Sound.h"
#include "miniaudio/miniaudio.h"
#include <string>
#include <vector>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool PlaySound(const std::string& filePath);
    void Shutdown();
    void SetListenerPosition(float x, float y, float z);
    void EnableEcho();
    void DisableEcho();


    ma_engine engine; // Rendu public pour permettre l'accès depuis Sound

private:
    bool Init();
    std::vector<Sound*> sounds;
    ma_node_graph nodeGraph;
    ma_delay_node delayNode;
    bool echoEnabled = false;
};

#endif // AUDIO_MANAGER_H