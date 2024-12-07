#include "pch.h"
#include "GameOverScene.h"
#include "UI.h"

void GameOverScene::Init()
{
	UI* ui = new UI(false, true, false, false);
	ui->SetPos({ 585, 400 });
	ui->SetSize({ 120, 50 });
	ui->SetFont(L"PFStardust.ttf", L"PF Stardust", 30, 40);
	ui->SetText(L"½ÃÀÛ");
	ui->ComponentInit(ui->GetSize(), ui->GetPos());
	AddObject(ui, LAYER::UI);
}

void GameOverScene::Update()
{
}
