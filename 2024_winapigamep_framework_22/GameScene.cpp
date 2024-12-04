#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Lerp.h"
#include "TimeManager.h"
#include "GameScene.h"

void Find(const vector<Tile> _tiles, int _cnt, int _findCnt, int _curValue, std::set<int>& _result);
GameScene::~GameScene()
{
	while (!nextTiles.empty())
	{
		Tile * tile = nextTiles[0];
		nextTiles.erase(nextTiles.begin());
		delete(tile);
	}

	delete(board);
	delete(backBoard);
}

void GameScene::Init()
{
	gameState = GAME_STATE::INIT;

	#pragma region Tile Render
	GET_SINGLE(ResourceManager)->TileInit(L"Button_empty.bmp", OBJ_TYPE::EMPTY);
	GET_SINGLE(ResourceManager)->TileInit(L"Button.bmp", OBJ_TYPE::MAIN);;
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Normal.bmp", OBJ_TYPE::NORMAL);
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Stone.bmp", OBJ_TYPE::STONE);
	#pragma endregion

	board = new Board();
	backBoard = new Board();

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			backBoard->data[i][j] = new Tile(0, CALC::PLUS, OBJ_TYPE::EMPTY);
			backBoard->data[i][j]->SetPos({(SCREEN_WIDTH / 2) + (j - 2) * 100, (SCREEN_HEIGHT / 2) + (i - 2) * 100});
			AddObject(backBoard->data[i][j], LAYER::EMPTY_TILE);
		}
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			board->data[i][j] = new Tile();
			AddObject(board->data[i][j], LAYER::OBJECT_TILE);
		}

	mainTile = new Tile(1, CALC::PLUS, OBJ_TYPE::MAIN);
	board->AddToBoard(mainTile, { 2,2 },
		backBoard->data[2][2]->GetPos());
	
	gameState = GAME_STATE::PLAY;
}

void GameScene::Update()
{
	if (CheckTarget())
	{
		gameState = GAME_STATE::INIT;
		StageInit();
		return;
	}

	//Debuging
	if (GET_KEYDOWN(KEY_TYPE::N))
	{
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << board->data[i][j]->ShowValue() << " ";
			}
			cout << endl;
		}
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_1))
		cout << "GameState : " << (int)gameState << endl;

	if (GET_KEYDOWN(KEY_TYPE::NUM_2))
	{
		for (int i = 0; i < nextTiles.size(); i++)
		{
			cout << nextTiles[i]->ShowValue() << endl;
		}
	}

	if (gameState == GAME_STATE::PLAY)
	{
		if (GET_KEYDOWN(KEY_TYPE::W)) Move({ 0, -1 });
		else if (GET_KEYDOWN(KEY_TYPE::A)) Move({ -1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::S)) Move({ 0, 1 });
		else if (GET_KEYDOWN(KEY_TYPE::D)) Move({ 1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::E)) AddTileRandom();
	}

	else if (gameState == GAME_STATE::MOVE)
	{
		if (timeCnt > 0)
		{
			if (timeCnt > gameTime)
			{
				cout << timeCnt << endl;
				timeCnt -= 0.01f;

				for (int x = 0; x < 5; x++)
				{
					for (int j = 0; j < 5; j++)
					{
						//if leo can't make Move
						board->data[x][j]->Move();
					}
				}
			}

			gameTime -= fDT;
		}
		else
		{
			//all dotTween fin
			gameState = GAME_STATE::PLAY;
		}
	}

	Scene::Update();
}

void GameScene::Move(Vec2 _dir)
{	
	gameState = GAME_STATE::MOVE;
	mainTile->merge = true;

	if (_dir.x + _dir.y < 0)
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				board->Move({ j, i }, _dir);
	}
	else if (_dir.x + _dir.y > 0)
	{
		for (int i = 4; i >= 0; i--)
			for (int j = 4; j >= 0; j--)
				board->Move({ j, i }, _dir);
	}

	gameTime = 1;
	timeCnt = 10;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board->data[i][j]->moveValue = 
				Lerp(board->data[i][j]->GetPos(), 
				backBoard->data[i][j]->GetPos(), gameTime / timeCnt);
		}
	}
}

void GameScene::FindTarget()
{
	std::set<int> result;
	//vector<Tile> allTile = nextTiles;

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

void GameScene::AddTile()
{
	CALC cal = (CALC)(rand() % 4);
	int value;
	if (cal == CALC::MINUS || cal == CALC::PLUS)
		value = rand() % 10 + 1;
	else
		value = rand() % 4 + 1;
	
	Tile* tile = new Tile(value, cal, OBJ_TYPE::NORMAL, false);
	nextTiles.push_back(tile);
}

void GameScene::AddTileRandom()
{
	vector<Vec2> arrP;
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board->data[i][j]->type == OBJ_TYPE::NONE)
				arrP.push_back({j, i});
		}
	}

	if (arrP.empty())
	{
		cout << "더 이상 넣을 데가 없어~" << endl;
		return;
	}

	Vec2 vec = arrP[rand() % arrP.size()];
	board->AddToBoard(nextTiles[0], vec, 
		backBoard->data[(int)vec.y][(int)vec.x]
		->GetPos());
	nextTiles.erase(nextTiles.begin(), nextTiles.begin()+1);
}

bool GameScene::CheckTarget() { return mainTile->value == targetNum; }

void GameScene::StageInit()
{
	cout << endl << "~~~~~~~~~~" << endl;
	cout << "STAGE Init" << endl;
	cout << "~~~~~~~~~~" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		AddTile();
	}

	gameState = GAME_STATE::PLAY;
	targetNum = 15;
}
























#pragma region  sfd
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