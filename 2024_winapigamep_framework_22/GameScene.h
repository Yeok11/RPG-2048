#pragma once 
#include "Tile.h"
#include "Scene.h"

class GameScene : public Scene
{
private:
    Tile board[5][5]; // 현재 보드
    vector<Tile> nextTiles; // 나올 타일들
    Tile main;
    int targetNum = 0;

public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;

    void FindTarget();
    void ChooseNextNums();
    bool CheckTarget();
};
