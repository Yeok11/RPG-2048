#include "pch.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "UI.h"
#include "AudioSource.h"

UI::UI()
	:m_isImage(true),
	m_isButton(false),
	m_isText(false)
{
	AddComponent<Image>();
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

void UI::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (!TryGetComponent<AudioSource>()) return;
	GetComponent<AudioSource>()->LoadSound(_key, _path, _isLoop);
}


void UI::Play(const wstring& _key)
{
	if (!TryGetComponent<AudioSource>()) return;
	GetComponent<AudioSource>()->Play(_key);
}

void UI::Stop(SOUND_CHANNEL _channel)
{
	if (!TryGetComponent<AudioSource>()) return;
	GetComponent<AudioSource>()->Stop(_channel);
}

void UI::SetVolume(SOUND_CHANNEL _channel, float _vol)
{
	if (!TryGetComponent<AudioSource>()) return;
	GetComponent<AudioSource>()->SetVolume(_channel, _vol);
}

void UI::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	if (!TryGetComponent<AudioSource>()) return;
	GetComponent<AudioSource>()->Pause(_channel, _ispause);
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

	//AddComponent<AudioSource>();

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
