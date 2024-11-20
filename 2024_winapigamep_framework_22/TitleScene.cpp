#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
void TitleScene::Init()
{
	Object* enemy = new Enemy({ 500.f,500.f }, { SCREEN_WIDTH / 2.f,150.f });
	AddObject(enemy, LAYER::ENEMY);
}

void TitleScene::Update()
{
	Scene::Update();
}
