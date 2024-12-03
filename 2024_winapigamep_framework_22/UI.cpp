#include "pch.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "UI.h"

UI::UI()
	:m_isImage(false),
	m_isButton(false),
	m_isText(false)
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
	MouseDetectObject::Update();
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

	MouseEnter += [&]() 
		{
			ComponentInit(GetSize() + Vec2(1.2f, 1.2f), GetPos()); 
			if (m_isImage) {
				GetComponent<Image>()->SetMultiple(2.1f, 2.1f);
				SetPos(GetPos() - Vec2(0.1f, 0.1f));
			}
		};
	MouseExit += [&]() 
		{ 
			ComponentInit(GetSize() - Vec2(1.2f, 1.2f), GetPos());
			if (m_isImage) {
				GetComponent<Image>()->SetMultiple(2, 2);
				SetPos(GetPos() + Vec2(0.1f, 0.1f));
			}
		};
}
