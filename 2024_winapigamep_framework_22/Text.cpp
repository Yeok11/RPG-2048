#include "pch.h"
#include "Text.h"
#include "ResourceManager.h"

Text::Text()
{
}

Text::~Text()
{
	ReleaseFont();
}

void Text::LateUpdate()
{
}

void Text::Render(HDC _hdc)
{
	GDISelector font(_hdc, m_font);
	Vec2 pos = GetOwner()->GetPos();
	Vec2 size = GetSize();
	TextOut(_hdc, (pos.x + size.x / 2 - 30), (pos.y + size.y / 2 - 30), m_text.c_str(), m_text.size());
}

void Text::SetFont(wstring fileName, wstring _fontName, int width, int height)
{
	wstring path = GET_SINGLE(ResourceManager)->GetResPath() + wstring(L"Font\\") + fileName;
	AddFontResource(path.c_str());
	m_font = CreateFont(width, height, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _fontName.c_str());
}

void Text::SetText(wstring _str)
{
	m_text = _str;
}

void Text::SetText(std::string _str)
{
	m_text = wstring().assign(_str.begin(), _str.end());
}

void Text::ReleaseFont()
{
	DeleteObject(m_font);
}
