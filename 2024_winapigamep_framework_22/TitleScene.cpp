#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
void TitleScene::Init()
{
	Object* enemy = new Enemy;
	enemy->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	enemy->SetSize({ 100.f,100.f });
	AddObject(enemy, LAYER::ENEMY);
}

void TitleScene::Update()
{
	Scene::Update();
}
