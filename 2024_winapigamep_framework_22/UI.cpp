#include "pch.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "UI.h"
#include "AudioSource.h"

UI::UI()
{
	AddComponent<Image>();
}

UI::UI(bool isImage, bool isText, bool isAudio, bool isButton)
{
	Init(isImage, isText, isButton, isAudio);
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
	if (TryGetComponent<Button>()) {
		GetComponent<Button>()->LateUpdate();
	}
}

void UI::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

#pragma region Button
void UI::AddListener(std::function<void()> act)
{
	if (!TryGetComponent<Button>()) return;
	GetComponent<Button>()->AddListener(act);
}
#pragma endregion

#pragma region Image
void UI::LoadAndSetting(const wstring& _key, const wstring& _path, float multipleWidth, float multipleHeight)
{
	if (!TryGetComponent<Image>()) return;
	GetComponent<Image>()->LoadAndSetting(_key, _path, multipleWidth, multipleHeight);
}
#pragma endregion

#pragma region Text
void UI::SetFont(wstring fileName, wstring _fontName, int width, int height)
{
	if (!TryGetComponent<Text>()) return;
	GetComponent<Text>()->SetFont(fileName, _fontName, width, height);
}

void UI::SetText(wstring _str)
{
	if (!TryGetComponent<Text>()) return;
	GetComponent<Text>()->SetText(_str);
}
#pragma endregion

#pragma region Audio
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
#pragma endregion

void UI::Init(bool isImage, bool isText, bool isButton, bool isAudio)
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
	if (isAudio) {
		AddComponent<AudioSource>();
	}

	MouseEnter += [&]() 
		{
			ComponentInit(GetSize() + Vec2(1.2f, 1.2f), GetPos()); 
			if (TryGetComponent<Image>()) {
				GetComponent<Image>()->SetMultiple(2.1f, 2.1f);
				SetPos(GetPos() - Vec2(0.1f, 0.1f));
			}
		};
	MouseExit += [&]() 
		{ 
			ComponentInit(GetSize() - Vec2(1.2f, 1.2f), GetPos());
			if (TryGetComponent<Image>()) {
				GetComponent<Image>()->SetMultiple(2, 2);
				SetPos(GetPos() + Vec2(0.1f, 0.1f));
			}
		};
}
