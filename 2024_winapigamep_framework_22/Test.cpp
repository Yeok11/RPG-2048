#include "pch.h"
#include "Test.h"
#include "Text.h"
#include "Image.h"

Test::Test()
{
	AddComponent<Text>();
	AddComponent<Image>();

	GetComponent<Text>()->Init({ 100, 100 }, { 100, 100 });
	GetComponent<Text>()->SetText(L"adsfgdedsgfjvgklfds");
	GetComponent<Text>()->SetFont(L"godoMaum.ttf", L"godoMaum");

	GetComponent<Image>()->Init({ 100,100 }, { 100,100 });
	GetComponent<Image>()->LoadAndSetting(L"UI", L"Texture\\Button1.bmp", 5, 5);
}

Test::~Test()
{
}

void Test::Update()
{
}

void Test::Render(HDC _hdc)
{
	GetComponent<Image>()->Render(_hdc);
	GetComponent<Text>()->Render(_hdc);
}
