#pragma once
#include "Scene.h"

class GameOverScene :
    public Scene
{
public:

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;

private:
	int score = 0;
	int highScore = 0;
};

