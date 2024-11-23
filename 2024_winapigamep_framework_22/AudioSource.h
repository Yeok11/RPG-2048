#pragma once
#include <algorithm>
#include "Component.h"
#include "ResourceManager.h"

class AudioSource :
    public Component
{
public:
    AudioSource();
    ~AudioSource() override;
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
public:
    void LoadSound(const wstring& _key, const wstring& _path, bool _isLoop);
    void Play(const wstring& _key);
    void Stop(SOUND_CHANNEL _channel);
    void SetVolume(SOUND_CHANNEL _channel, float _vol);
    void Pause(SOUND_CHANNEL _channel, bool _ispause);
};

