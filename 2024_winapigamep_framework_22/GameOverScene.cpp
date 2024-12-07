#include "pch.h"
#include "GameOverScene.h"
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
}

void GameOverScene::Update()
{
}
