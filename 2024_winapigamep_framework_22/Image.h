#pragma once
#include "Component.h"
#include "Object.h"

class Texture;
class Image : public Component
{
public:
	Image();
	~Image() override;
public:
	void LoadAndSetting(const wstring& _key, const wstring& _path, float multipleWidth, float multipleHeight);
	void TileLoadSetting(const OBJ_TYPE _type, float multipleWidth, float multipleHeight);
	void SetMultiple(float widthMultiple, float heightMultiple);
	void LateUpdate() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
	float m_multipleWidth;
	float m_multipleHeight;
};