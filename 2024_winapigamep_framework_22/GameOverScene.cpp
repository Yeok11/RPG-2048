#include "pch.h"
#include "GameOverScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UI.h"

void GameOverScene::Init()
{
	UI* ui = new UI(false, true, false, false);
	ui->SetPos({ SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 80 });
	ui->SetSize({ 120, 50 });
	ui->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	ui->SetText(L"Game Over");
	ui->ComponentInit(ui->GetSize(), ui->GetPos());
	AddObject(ui, LAYER::UI);

	UI* sc = new UI(false, true, false, false);
	sc->SetPos({ SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 80 });
	sc->SetSize({ 120, 50 });
	sc->SetFont(L"PFStardust.ttf", L"PF Stardust", 60, 80);
	sc->SetText(L"Game Over");
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
		PostQuitMessage(0);
		//GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}
