#include "pch.h"
#include "UI.h"
#include "Image.h"
#include "Button.h"
#include "Text.h"

UI::UI()
{
}

UI::UI(bool isImage, bool isText, bool isButton)
{
	Init(isImage, isText, isButton);
}

UI::~UI()
{
}

void UI::Update()
{
	
}

void UI::LateUpdate()
{
	if (m_isButton) {
		GetComponent<Button>()->LateUpdate();
	}
}

void UI::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void UI::AddListener(std::function<void()> act)
{
	if (!m_isButton) {
		cout << "this object is not Button" << endl;
		return;
	}

	GetComponent<Button>()->AddListener(act);
}

void UI::LoadAndSetting(const wstring& _key, const wstring& _path, int multipleWidth, int multipleHeight)
{
	if (!m_isImage) {
		cout << "this object is not Image" << endl;
		return;
	}

	GetComponent<Image>()->LoadAndSetting(_key, _path, multipleWidth, multipleHeight);
}

void UI::SetFont(wstring fileName, wstring _fontName, int width, int height)
{
	if (!m_isText) {
		cout << "this object is not Text" << endl;
		return;
	}

	GetComponent<Text>()->SetFont(fileName, _fontName, width, height);
}

void UI::SetText(wstring _str)
{
	if (!m_isText) {
		cout << "this object is not Text" << endl;
		return;
	}

	GetComponent<Text>()->SetText(_str);
}

void UI::Init(bool isImage, bool isText, bool isButton)
{
	if (isImage) {
		AddComponent<Image>();
	}
	if (isText) {
		AddComponent<Text>();
	}
	if (isButton) {
		AddComponent<Button>();
	}

	m_isImage = isImage;
	m_isButton = isButton;
	m_isText = isText;

	ComponentInit(GetSize(), GetPos());
}
