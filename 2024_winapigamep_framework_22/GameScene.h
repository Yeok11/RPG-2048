#pragma once 
#include "Scene.h"
#include "Board.h"
#include "UI.h"

class GameScene : public Scene
{
private:
    Board * backBoard; // 현재 배경 보드
    Board * board; // 현재 보드
    vector<Tile*> nextTiles; // 나올 타일들
    GAME_STATE gameState;

    UI* targetTxt;
    UI* timeTxt;
    UI* scoreTxt;
    UI* resetSkill;

    Tile* mainTile;
    int targetNum = 1;
    int timeCnt = 0;
    int score = 0;
    
    //skill
private:
    int skill_Reset = 0;

    //Time
private:
    float moveTime;
    float gameTime;
    float delay = 0;

public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    ~GameScene() override;
    void Move(Vec2 _dir);

private:
    bool CheckTarget();

    void AddTile();
    void AddTileRandom();
    void SetScore(int _value = -99) 
    {
        if (_value == -99) score++;
        else score = _value;

        if (score % 10 == 0 && score != 0)
        {
            skill_Reset++;
            resetSkill->SetText(L"R : " + std::to_wstring(skill_Reset));
        }

        scoreTxt->SetText(L"SCORE : " + std::to_wstring(score));
    }

    void Skill_Init();

    //Find Target
    void FindTarget();
};
