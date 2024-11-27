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
			backBoard[i][j]->SetSize({100, 100});
			backBoard[i][j]->SetPos({(SCREEN_WIDTH / 2) + (i - 2) * 100, (SCREEN_HEIGHT / 2) + (j - 2) * 100});
			AddObject(backBoard[i][j], LAYER::EMPTY_TILE);
			backBoard[i][j]->ComponentInit(backBoard[i][j]->GetSize(), backBoard[i][j]->GetPos());
		}
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[i][j] = new Tile();

	board[2][2] = new Tile(1, CALCULATE::PLUS, OBJ_TYPE::MAIN);
	board[2][2]->SetSize({ 100, 100 });
	board[2][2]->SetPos({ (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)});
	AddObject(board[2][2], LAYER::OBJECT_TILE);
	board[2][2]->ComponentInit(board[2][2]->GetSize(), board[2][2]->GetPos());

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

GameScene::~GameScene()
{

}

void GameScene::Move(char _dir)
{
	int cnt = 0;

	if (_dir == 'W' || _dir == 'S')
	{
		for (int j = 0; j < 5; j++)
		{

			for (int i = 0; i < 5; i++)
			{

			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{

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