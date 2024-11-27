#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "GameScene.h"
#include "ResourceManager.h"

void Find(const vector<Tile> _tiles, int _cnt, int _findCnt, int _curValue, std::set<int>& _result);

void GameScene::Init()
{
	GET_SINGLE(ResourceManager)->TileInit(L"Button_empty.bmp", OBJ_TYPE::EMPTY);
	GET_SINGLE(ResourceManager)->TileInit(L"Button.bmp", OBJ_TYPE::MAIN);;
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Normal.bmp", OBJ_TYPE::NORMAL);
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Stone.bmp", OBJ_TYPE::STONE);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			backBoard[i][j] = new Tile(0, CALC::PLUS, OBJ_TYPE::EMPTY);


			AddObject(backBoard[i][j], LAYER::EMPTY_TILE);
		}
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[i][j] = new Tile();

	board[2][2] = new Tile(2, CALCULATE::PLUS, OBJ_TYPE::MAIN);
	AddObject(board[2][2], LAYER::OBJECT_TILE);

	board[2][3] = new Tile(1, CALCULATE::PLUS, OBJ_TYPE::MAIN);
	AddObject(board[2][3], LAYER::OBJECT_TILE);

	board[1][2] = new Tile(1, CALCULATE::PLUS, OBJ_TYPE::MAIN);
	AddObject(board[1][2], LAYER::OBJECT_TILE);

	//FindTarget();
}

void GameScene::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::W)) Move('W');
	else if (GET_KEYDOWN(KEY_TYPE::A)) Move('A');
	else if (GET_KEYDOWN(KEY_TYPE::S)) Move('S');
	else if (GET_KEYDOWN(KEY_TYPE::D)) Move('D');

	//Debuging
	if (GET_KEYDOWN(KEY_TYPE::N))
	{
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << board[i][j]->ShowValue() << " ";
			}
			cout << endl;
		}
	}
}

void GameScene::Move(char _dir)
{	
	vector<Tile*> filedTiles;

	if (_dir == 'W' || _dir == 'S')
	{
		for (int j = 0; j < 5; j++)
		{
			filedTiles = vector<Tile*>();
			for (int i = 0; i < 5; i++)//타일들 빼기
			{
				if (board[i][j]->type != OBJ_TYPE::NONE) 
				{
					filedTiles.push_back(board[i][j]);
					board[i][j] = new Tile();
				}
			}

			if (_dir == 'W') //다시 넣기
			{
				for (int i = 0; i < filedTiles.size(); i++)
					board[i][j] = filedTiles[i];
			}
			else
			{
				for (int i = 0; i < filedTiles.size(); i++)
					board[4 - i][j] = filedTiles[filedTiles.size() - i - 1];
			}
		}
	}
	else
	{
		for (int j = 0; j < 5; j++)
		{
			filedTiles = vector<Tile*>();
			for (int i = 0; i < 5; i++)//타일들 빼기
			{
				if (board[j][i]->type != OBJ_TYPE::NONE)
				{
					filedTiles.push_back(board[j][i]);
					board[j][i] = new Tile();
				}
			}

			if (_dir == 'A') //다시 넣기
			{
				for (int i = 0; i < filedTiles.size(); i++)
					board[j][i] = filedTiles[i];
			}
			else if (_dir == 'D')
			{
				for (int i = 0; i < filedTiles.size(); i++)
					board[j][4 - i] = filedTiles[filedTiles.size() - i - 1];
			}
		}
	}
}

void GameScene::FindTarget()
{
	std::set<int> result;
	vector<Tile> allTile = nextTiles;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//if (board[i][j]->type != OBJ_TYPE::EMPTY)
			//	allTile.push_back(board[i][j]);
		}
	}

	//Find(allTile, 0, 0, mainTile->value, result);
}

void GameScene::ChooseNextNums()
{
}

bool GameScene::CheckTarget()
{
	return mainTile->value == targetNum;
}























#pragma region  값 지정 알고리듬
int NumberToInt(const int _oldValue, const Tile _curValue)
{
	switch (_curValue.cal)
	{
	case CALC::PLUS:
		return _oldValue + _curValue.value;
	case CALC::MINUS:
		return _oldValue - _curValue.value;
	case CALC::MULTIPLY:
		return _oldValue * _curValue.value;
	case CALC::DIVIDE:
		return _oldValue / _curValue.value;
	}

	cout << "error";
	return 0;
}

void Find(const vector<Tile> _tiles, int _cnt,
	int _findCnt, int _curValue, std::set<int>& _result)
{
	if (_cnt++ == _tiles.size())
	{
		_result.insert(_curValue);
		return;
	}

	Find(_tiles, _cnt, _findCnt + 1, NumberToInt(_curValue, _tiles[_cnt - 1]), _result);
	Find(_tiles, _cnt, _findCnt, _curValue, _result);
}
#pragma endregion