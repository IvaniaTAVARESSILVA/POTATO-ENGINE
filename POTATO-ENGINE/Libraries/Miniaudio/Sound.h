#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "miniaudio/miniaudio.h"
#include <string>
#include <thread>
#include <atomic>

class Sound {
public:
    Sound(ma_engine* engine, const std::string& filePath);
    ~Sound();

    void Play();
    void Pause();
    void Resume();
    void Restart();  // Red�marrer depuis le d�but

    void SetVolume(float volume);
    void SetLooping(bool loop);

    // Effet 3D
    void SetPosition(float x, float y, float z);
    void SetPitch(float pitch);
    void Enable3DMovement(bool enable);  // Activer/d�sactiver le mouvement 3D

private:
    ma_sound sound;

    // Gestion du mouvement 3D
    void Start3DMovement();            // D�marrer le mouvement 3D
    void Stop3DMovement();             // Arr�ter le mouvement 3D
    void Update3DPosition();           // Mise � jour continue de la position

    std::atomic<bool> enable3DMovement; // Indique si le mouvement 3D est activ�
    std::atomic<bool> running3DMovement; // Indique si le thread de mouvement est en cours
    std::thread movementThread;        // Thread pour g�rer le mouvement 3D

    // Variables de position
    float soundX;
    float soundY;
    float soundZ;
};

#endif // SOUND_H
