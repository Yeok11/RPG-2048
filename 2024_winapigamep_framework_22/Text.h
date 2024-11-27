#pragma once
#include "Component.h"
#include "GDISelector.h"
#include "Object.h"

class Text :
    public Component
{
public:
    Text();
    ~Text() override;
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
    void SetFont(wstring fileName, wstring _fontName, int width, int height);
    void SetText(wstring _str);
    void ReleaseFont();
private:
    HFONT m_font;
    wstring m_text;
};

