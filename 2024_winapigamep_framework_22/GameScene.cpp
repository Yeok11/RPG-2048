#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "GameScene.h"

void Find(const vector<Tile> _tiles, int _cnt, int _findCnt, int _curValue, std::set<int>& _result);

void GameScene::Init()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			backBoard[i][j] = new Tile();
			AddObject(backBoard[i][j], LAYER::NONE_TILE);
		}

	FindTarget();
}

void GameScene::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::W))
	{
		
	}
	else if (GET_KEYDOWN(KEY_TYPE::A))
	{

	}
	else if (GET_KEYDOWN(KEY_TYPE::S))
	{

	}
	else if (GET_KEYDOWN(KEY_TYPE::D))
	{

	}

	//Debuging
	if (GET_KEYDOWN(KEY_TYPE::N))
	{
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << board[i][j]->ShowValue();
			}
			cout << endl;
		}
	}
}

void GameScene::Move(char _dir)
{
	if (_dir == 'W' || _dir == 'S')
	{
		for (int j = 0; j < 5; j++)
		{
			
		}
		
	}
	else
	{

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