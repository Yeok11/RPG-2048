#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "UI.h"

void TitleScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.mp3", true);
#pragma region Btn
	UI* startBtn = new UI(true, true, false, true);
	startBtn->SetPos({ 585, 400 });
	startBtn->SetSize({ 120, 50 });
	startBtn->LoadAndSetting(L"BtnUI", L"Texture\\Button_Long.bmp", 2, 2);
	startBtn->SetFont(L"PFStardust.ttf", L"PF Stardust", 30, 40);
	startBtn->SetText(L"시작");
	startBtn->ComponentInit(startBtn->GetSize(), startBtn->GetPos());
	startBtn->AddListener([]() { GET_SINGLE(SceneManager)->LoadScene(L"GameScene"); });
	startBtn->Play(L"aaa");
	AddObject(startBtn, LAYER::UI);

	UI* exitBtn = new UI(true, true, false, true);
	exitBtn->SetPos({ 585, 500 });
	exitBtn->SetSize({ 120, 50 });
	exitBtn->LoadAndSetting(L"BtnUI", L"Texture\\Button_Long.bmp", 2, 2);
	exitBtn->SetFont(L"PFStardust.ttf", L"PF Stardust", 30, 40);
	exitBtn->SetText(L"나가기");
	exitBtn->ComponentInit(exitBtn->GetSize(), exitBtn->GetPos());
	exitBtn->AddListener([]() { PostQuitMessage(0); });
	AddObject(exitBtn, LAYER::UI);
#pragma endregion

#pragma region Text
	UI* titleText = new UI(false, true, false, false);
	titleText->SetPos({ 500, 200 });
	titleText->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	titleText->SetText(L"MergeCalc");
	AddObject(titleText, LAYER::UI);
#pragma endregion
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, 0.2f);
}

void TitleScene::Update()
{
	Scene::Update();
}
