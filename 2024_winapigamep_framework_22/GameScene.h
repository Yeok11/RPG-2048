#pragma once 
#include "Scene.h"
class GameScene : public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;

    //Tile board[5][5]; // ���� ����
    //vector<Tile> nextTiles; // ���� Ÿ�ϵ�
};

