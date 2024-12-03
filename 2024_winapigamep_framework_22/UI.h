#pragma once
#include <functional>
#include "MouseDetectObject.h"

class UI :
    public MouseDetectObject
{
public:
    UI();
    UI(bool isImage, bool isText, bool isButton = false);
    ~UI() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

    // Button
    void AddListener(std::function<void()> act);

    // Image
    void LoadAndSetting(const wstring& _key, const wstring& _path, int multipleWidth, int multipleHeight);

    // Text
    void SetFont(wstring fileName, wstring _fontName, int width, int height);
    void SetText(wstring _str);
private:
    void Init(bool isImage, bool isText, bool isButton);
    bool m_isImage;
    bool m_isButton;
    bool m_isText;
};

