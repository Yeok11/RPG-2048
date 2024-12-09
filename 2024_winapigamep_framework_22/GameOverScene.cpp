#include "pch.h"
#include "GameOverScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "UI.h"

void GameOverScene::Init()
{
	score = GET_SINGLE(ScoreManager)->GetScore();
	highScore = GET_SINGLE(ScoreManager)->GetHighScore();

	UI* ui = new UI(false, true, false, false);
	ui->SetPos({ SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 150 });
	ui->SetSize({ 120, 50 });
	ui->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	ui->SetText(L"HghScore : " + std::to_wstring(highScore));
	ui->ComponentInit(ui->GetSize(), ui->GetPos());
	AddObject(ui, LAYER::UI);

	UI* sc = new UI(false, true, false, false);
	sc->SetPos({ SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 });
	sc->SetSize({ 120, 50 });
	sc->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	sc->SetText(L"Score : " + std::to_wstring(score));
	sc->ComponentInit(sc->GetSize(), sc->GetPos());
	AddObject(sc, LAYER::UI);


	UI* ui2 = new UI(false, true, false, false);
	ui2->SetPos({ SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 80 + 150 });
	ui2->SetSize({ 120, 50 });
	ui2->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	ui2->SetText(L"Press Enter");
	ui2->ComponentInit(ui2->GetSize(), ui2->GetPos());
	AddObject(ui2, LAYER::UI);
}

void GameOverScene::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}
