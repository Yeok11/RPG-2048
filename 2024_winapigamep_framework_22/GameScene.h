#pragma once 
#include "Scene.h"
class GameScene : public Scene
{
public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;

    //Tile board[5][5]; // 현재 보드
    //vector<Tile> nextTiles; // 나올 타일들
};

