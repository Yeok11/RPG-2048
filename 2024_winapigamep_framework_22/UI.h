#pragma once
#include <functional>
#include "MouseDetectObject.h"
#include "ResourceManager.h"

class UI :
    public MouseDetectObject
{
public:
    UI();
    UI(bool isImage, bool isText, bool isAudio, bool isButton = false);
    ~UI() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

    // Button
    void AddListener(std::function<void()> act);

    // Image
    void LoadAndSetting(const wstring& _key, const wstring& _path, float multipleWidth, float multipleHeight);

    // Text
    void SetFont(wstring fileName, wstring _fontName, int width, int height);
    void SetText(wstring _str);

    // Audio
    void LoadSound(const wstring& _key, const wstring& _path, bool _isLoop);
    void Play(const wstring& _key);
    void Stop(SOUND_CHANNEL _channel);
    void SetVolume(SOUND_CHANNEL _channel, float _vol);
    void Pause(SOUND_CHANNEL _channel, bool _ispause);
private:
    void Init(bool isImage, bool isText, bool isButton, bool isAudio);
};

