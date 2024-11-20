#include "pch.h"
#include "Text.h"
#include <string>

Text::Text()
{
}

Text::~Text()
{
}

void Text::LateUpdate()
{
}

void Text::Render(HDC _hdc)
{
	GDISelector font(_hdc, m_font);
	Vec2 pos = GetOffSetPos();
	TextOut(_hdc, pos.x, pos.y, m_text.c_str(), m_text.size());
}

void Text::SetFont(wstring fileName, wstring _fontName)
{
	AddFontResource(fileName.c_str());
	m_font = CreateFont(0, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _fontName.c_str());
}

void Text::SetText(wstring _str)
{
	m_text = _str;
}

void Text::ReleaseFont()
{
	//DeleteObject(m_font);
}
