#pragma once 
#include "Scene.h"
#include "Board.h"

class GameScene : public Scene
{
private:
    Board * backBoard; // 현재 배경 보드
    Board * board; // 현재 보드
    vector<Tile*> nextTiles; // 나올 타일들

    GAME_STATE gameState;

    Tile* mainTile;
    int targetNum = 1;

public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    ~GameScene() override;

    bool CheckTarget();
    void Move(Vec2 _dir);

private:
    void StageInit();
    void FindTarget();
    void AddTile();
    void AddTileRandom();
};
