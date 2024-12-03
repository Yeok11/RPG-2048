#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "UI.h"

void TitleScene::Init()
{
#pragma region Btn
	UI* startBtn = new UI(true, true, true);
	startBtn->SetPos({ 585, 400 });
	startBtn->SetSize({ 120, 50 });
	startBtn->LoadAndSetting(L"BtnUI", L"Texture\\Button_Long.bmp", 2, 2);
	startBtn->SetFont(L"PFStardust.ttf", L"PF Stardust", 30, 40);
	startBtn->SetText(L"시작");
	startBtn->ComponentInit(startBtn->GetSize(), startBtn->GetPos());
	startBtn->AddListener([]() { GET_SINGLE(SceneManager)->LoadScene(L"GameScene"); });
	AddObject(startBtn, LAYER::UI);

	UI* exitBtn = new UI(true, true, true);
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
	UI* titleText = new UI(false, true, false);
	titleText->SetPos({ 600, 200 });
	titleText->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	titleText->SetText(L"몰?루");
	AddObject(titleText, LAYER::UI);
#pragma endregion
}

void TitleScene::Update()
{
	Scene::Update();
}
