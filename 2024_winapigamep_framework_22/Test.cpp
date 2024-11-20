#include "pch.h"
#include "Test.h"
#include "Text.h"

Test::Test()
{
	AddComponent<Text>();
	GetComponent<Text>()->Init({ 100, 100 }, { 100, 100 });
	GetComponent<Text>()->SetFont(L"godoMaum.ttf", L"godoMaum");
	GetComponent<Text>()->SetText(L"�ȳ�");
}

Test::~Test()
{
}

void Test::Update()
{
}

void Test::Render(HDC _hdc)
{
	GetComponent<Text>()->Render(_hdc);
}
