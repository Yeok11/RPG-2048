#include "pch.h"
#include "Board.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Text.h"
#include "GameScene.h"

Board::~Board()
{
	
}

void Board::Move(Vec2 _lastPos, Vec2 _dir)
{
	int posX = _lastPos.x, posY = _lastPos.y;
	int moveX = posX + _dir.x, moveY = posY + _dir.y;

	if (moveX >= 5 || moveY >= 5) return;
	if (moveX < 0 || moveY < 0) return;

	if (data[posY][posX]->type == OBJ_TYPE::NONE) return;

	#pragma region Move
	if (data[moveY][moveX]->type == OBJ_TYPE::MAIN && data[moveY][moveX]->merge)
	{
		Tile* main = data[moveY][moveX];

		cout << "merge Main : " << moveX << " / " << moveY << endl;
		main->Calculate(data[posY][posX]);

		//delete
		GET_SINGLE(EventManager)->DeleteObject(data[posY][posX]);
		data[posY][posX] = new Tile();

		main->merge = false;
		if (main->value < 0) main->cal = CALC::MINUS;
		else main->cal = CALC::PLUS;


		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(data[posY][posX], LAYER::OBJECT_TILE);
		main->GetComponent<Text>()->SetText(main->ShowValue());
	}

	else if (data[moveY][moveX]->type == OBJ_TYPE::NONE)
	{
		//cout << posX << " / " << posY << " -> " << moveX << " / " << moveY << "  move" << endl;

		Tile* temp = data[moveY][moveX];
		data[moveY][moveX] = data[posY][posX];
		data[posY][posX] = temp;

		Move({ moveX, moveY }, _dir);
	}

	else if (data[posY][posX]->type == OBJ_TYPE::MAIN && data[posY][posX]->merge)
	{
		//cout << moveX << " / " << moveY << "  : main" << endl;

		Tile* before = data[moveY][moveX];
		data[posY][posX]->Calculate(before);

		data[moveY][moveX] = data[posY][posX];
		data[posY][posX] = new Tile();
		
		GET_SINGLE(SceneManager)->GetCurrentScene()
			->AddObject(data[posY][posX], LAYER::OBJECT_TILE);

		Tile* main = data[moveY][moveX];
		main->merge = false;
		main->cal = main->value < 0 ? CALC::MINUS : CALC::PLUS;
		main->GetComponent<Text>()->SetText(main->ShowValue());

		GET_SINGLE(EventManager)->DeleteObject(before);
	}
#pragma endregion
}

void Board::ClearBoard()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (data[i][j]->type != OBJ_TYPE::MAIN && data[i][j]->type != OBJ_TYPE::NONE)
			{
				GET_SINGLE(EventManager)->DeleteObject(data[i][j]);
				data[i][j] = new Tile();
				GET_SINGLE(SceneManager)->GetCurrentScene()
					->AddObject(data[i][j], LAYER::OBJECT_TILE);
			}
		}
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

void Board::AddToBoardNoAddObject(Tile* _tile, Vec2 _arrPos, Vec2 _tilePos)
{
	int x = _arrPos.x, y = _arrPos.y;

	_tile->SetPos(_tilePos);
	_tile->Init();

	GET_SINGLE(EventManager)->DeleteObject(data[y][x]);

	data[y][x] = _tile;
}
