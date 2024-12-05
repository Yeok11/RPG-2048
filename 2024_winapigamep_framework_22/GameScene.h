#pragma once 
#include "Scene.h"
#include "Board.h"

class GameScene : public Scene
{
private:
    Board * backBoard; // ���� ��� ����
    Board * board; // ���� ����
    vector<Tile*> nextTiles; // ���� Ÿ�ϵ�
    GAME_STATE gameState;

    Tile* mainTile;
    int targetNum = 1;
    float gameTime;
    int timeCnt = 0;

public:
    // Scene��(��) ���� ��ӵ�
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
