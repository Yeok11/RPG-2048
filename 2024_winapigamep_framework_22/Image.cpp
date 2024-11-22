#include "pch.h"
#include "Image.h"
#include "Texture.h"
#include "ResourceManager.h"

Image::Image()
	:m_pTex(nullptr),
	m_multipleWidth(1),
	m_multipleHeight(1)
{
}

Image::~Image()
{
}

void Image::LoadAndSetting(const wstring& _key, const wstring& _path, int multipleWidth, int multipleHeight)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_key, _path);
	m_multipleWidth = multipleWidth;
	m_multipleHeight = multipleHeight;
}

void Image::LateUpdate()
{
}

void Image::Render(HDC _hdc)
{
	Vec2 vPos = GetOffSetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width * m_multipleWidth, height * m_multipleHeight,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));
}
