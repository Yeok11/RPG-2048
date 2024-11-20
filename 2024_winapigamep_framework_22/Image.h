#pragma once
#include "Component.h"
class Texture;
class Image : public Component
{
public:
	Image();
	~Image() override;
public:
	void LoadAndSetting(const wstring& _key, const wstring& _path, int multipleWidth, int multipleHeight);
	void LateUpdate() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
	int m_multipleWidth;
	int m_multipleHeight;
};

