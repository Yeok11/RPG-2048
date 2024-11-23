#include "pch.h"
#include "Test.h"
#include "Text.h"
#include "Image.h"
#include "Button.h"

Test::Test()
{
	AddComponent<Text>();
	AddComponent<Image>();
	AddComponent<Button>();

	GetComponent<Text>()->SetText(L"adsfgdedsgfjvgklfds");
	GetComponent<Text>()->SetFont(L"godoMaum.ttf", L"godoMaum", 40, 30);

	GetComponent<Image>()->LoadAndSetting(L"UI", L"Texture\\Button1.bmp", 5, 5);

	GetComponent<Button>()->AddListener([]() {cout << "a" << endl; });
	GetComponent<Button>()->AddListener([]() {cout << "b" << endl; });

	ComponentInit({100,100}, {100,100});
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

void Test::LateUpdate()
{
	GetComponent<Button>()->LateUpdate();
}
