#pragma once
#include "Tile.h"

class Board
{
public:
	Board() {}
	~Board();
	Tile * data[5][5];


	void Move(Vec2 _lastPos, Vec2 _dir);
	void AddToBoard(Tile* _tile, Vec2 _arrPos, Vec2 _tilePos);
	void AddToBoardNoAddObject(Tile* _tile, Vec2 _arrPos, Vec2 _tilePos);
};

