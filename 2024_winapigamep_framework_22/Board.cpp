#include "pch.h"
#include "Board.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "GameScene.h"

void Board::Move(Vec2 _lastPos, Vec2 _dir)
{
	int posX = _lastPos.x, posY = _lastPos.y;
	int moveX = posX + _dir.x, moveY = posY + _dir.y;

	cout << posX << " / " << posY << " Check" << endl;

	if (moveX >= 5 || moveY >= 5) return;
	if (moveX < 0 || moveY < 0) return;

	if (data[posY][posX]->type == OBJ_TYPE::NONE) return;
	cout << "is Not None" << endl;


	if (data[moveY][moveX]->type == OBJ_TYPE::MAIN)
	{
		data[moveY][moveX]->Calculate(data[posY][posX]);
		GET_SINGLE(EventManager)->DeleteObject(data[posY][posX]);
		data[posY][posX] = new Tile();
	}
	else if (data[moveY][moveX]->type == OBJ_TYPE::NONE)
	{
		cout << posX << " / " << posY << " -> " << moveX << " / " << moveY << "  move" << endl;

		Tile* temp = data[moveY][moveX];
		data[moveY][moveX] = data[posY][posX];
		data[posY][posX] = temp;

		Move({ moveX, moveY }, _dir);
	}
}

void Board::AddToBoard(Tile* _tile, Vec2 _arrPos, Vec2 _tilePos)
{
	int x = _arrPos.x, y = _arrPos.y;

	_tile->SetPos(_tilePos);
	_tile->Init();

	GET_SINGLE(EventManager)->DeleteObject(data[y][x]);

	data[y][x] = _tile;
	
	GET_SINGLE(SceneManager)->GetCurrentScene()
		->AddObject(_tile, LAYER::OBJECT_TILE);
}