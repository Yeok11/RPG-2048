#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Test.h"
void TitleScene::Init()
{
	Object* test = new Test;
	test->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	test->SetSize({ 100.f, 100.f });
	AddObject(test, LAYER::DEFAULT);
}

void TitleScene::Update()
{
	Scene::Update();
}
