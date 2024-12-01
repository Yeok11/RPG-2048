#pragma once 
#include "Tile.h"
#include "Scene.h"

class GameScene : public Scene
{
private:
    Tile * backBoard[5][5]; // ���� ����
    Tile * board[5][5]; // ���� ����
    vector<Tile> nextTiles; // ���� Ÿ�ϵ�

    Tile* mainTile;
    int targetNum = 0;

public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    ~GameScene() override;

    void Move(char _dir);
    void FindTarget();
    void ChooseNextNums();
    void AddTile(Tile tile, Vec2 pos, Vec2 size, int i, int j);
    bool CheckTarget();
};
