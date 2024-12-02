#include "pch.h"
#include "TitleScene.h"
#include "UI.h"
#include "SceneManager.h"

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
	startBtn->AddListener([]() {GET_SINGLE(SceneManager)->LoadScene(L"GameScene"); });
	AddObject(startBtn, LAYER::UI);

	UI* exitBrn = new UI(true, true, true);
	exitBrn->SetPos({ 585, 500 });
	exitBrn->SetSize({ 200, 50 });
	exitBrn->LoadAndSetting(L"BtnUI", L"Texture\\Button_Long.bmp", 2, 2);
	exitBrn->SetFont(L"PFStardust.ttf", L"PF Stardust", 30, 40);
	exitBrn->SetText(L"나가기");
	exitBrn->ComponentInit(startBtn->GetSize(), startBtn->GetPos());
	exitBrn->AddListener([]() { PostQuitMessage(0); });
	AddObject(exitBrn, LAYER::UI);
#pragma endregion

#pragma region Text
	UI* titleText = new UI(false, true, false);
	titleText->SetPos({ 470, 200 });
	titleText->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	titleText->SetText(L"대충 게임 이름");
	AddObject(titleText, LAYER::UI);
#pragma endregion
	
}

void TitleScene::Update()
{
	Scene::Update();
}
