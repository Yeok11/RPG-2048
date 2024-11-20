#pragma once
#include "Component.h"
#include "GDISelector.h"
class Text :
    public Component
{
public:
    Text();
    ~Text() override;
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
    void SetFont(wstring fileName, wstring _fontName);
    void SetText(wstring _str);
    void ReleaseFont();
private:
    HFONT m_font;
    wstring m_text;
};

