#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Lerp.h"
#include "TimeManager.h"
#include "GameScene.h"
#include "UI.h"

GameScene::~GameScene()
{
	/*while (!nextTiles.empty())
	{
		Tile * tile = nextTiles[0];
		nextTiles.erase(nextTiles.begin());
		delete(tile);
	}*/

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

	#pragma region Board Setting
	board = new Board();
	backBoard = new Board();

	#pragma region AllTile Init
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			backBoard->data[i][j] = new Tile(0, CALC::PLUS, OBJ_TYPE::EMPTY);
			backBoard->data[i][j]->SetPos({ (SCREEN_WIDTH / 2) + (j - 2) * 100, (SCREEN_HEIGHT / 2) + (i - 2) * 100 });
			AddObject(backBoard->data[i][j], LAYER::EMPTY_TILE);
		}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			board->data[i][j] = new Tile();
			AddObject(board->data[i][j], LAYER::OBJECT_TILE);
		}
#pragma endregion

	mainTile = new Tile(1, CALC::PLUS, OBJ_TYPE::MAIN);
	board->AddToBoard(mainTile, { 2,2 }, backBoard->data[2][2]->GetPos());
	#pragma endregion

	#pragma region UI Setting
	UI* tilesImage = new UI();
	tilesImage->SetPos({ 1050, 100 });
	tilesImage->LoadAndSetting(L"BtnUI_UP", L"Texture\\Button_Long_Up.bmp", 10, 10);
	tilesImage->ComponentInit(tilesImage->GetSize(), tilesImage->GetPos());
	AddObject(tilesImage, LAYER::EMPTY_TILE);
	#pragma endregion
	
	gameState = GAME_STATE::PLAY;
}

void GameScene::Update()
{
	if (CheckTarget())
	{
		gameState = GAME_STATE::INIT;
		StageInit();
		int x = 200;
		for (auto& tile : nextTiles) {
			tile->SetPos({ 1100, x });
			tile->ComponentInit(tile->GetSize(), tile->GetPos());
			AddObject(tile, LAYER::OBJECT_TILE);
			x += 200;
		}
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
				wcout << board->data[i][j]->ShowValue() << " ";
			}
			cout << endl;
		}
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_1))
		cout << "GameState : " << (int)gameState << endl;

	if (GET_KEYDOWN(KEY_TYPE::NUM_2))
		for (int i = 0; i < nextTiles.size(); i++)
			wcout << nextTiles[i]->ShowValue() << endl;

	if (GET_KEYDOWN(KEY_TYPE::NUM_3)) FindTarget();

	

	if (gameState == GAME_STATE::MOVE)
	{
		if (timeCnt > 0)
		{
			if (timeCnt > gameTime)//if leo can't make Move
			{
				timeCnt -= 0.01f;

				for (int x = 0; x < 5; x++)
					for (int j = 0; j < 5; j++)
						board->data[x][j]->Move();
			}
			gameTime -= fDT;
		}
		else //all dotTween fin
		{
			AddTileRandom();
			gameState = GAME_STATE::PLAY;
		}
	}

	else if (CheckTarget() || gameState == GAME_STATE::INIT)
	{
		gameState = GAME_STATE::INIT;
		StageInit();
		FindTarget();
		return;
	}
	
	else if (gameState == GAME_STATE::PLAY)
	{
		if (GET_KEYDOWN(KEY_TYPE::W)) Move({ 0, -1 });
		else if (GET_KEYDOWN(KEY_TYPE::A)) Move({ -1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::S)) Move({ 0, 1 });
		else if (GET_KEYDOWN(KEY_TYPE::D)) Move({ 1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::E)) AddTileRandom();
	}

	Scene::Update();
}

void GameScene::Move(Vec2 _dir)
{	
	gameState = GAME_STATE::MOVE;
	mainTile->merge = true;

	#pragma region Arr Move
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
#pragma endregion

	gameTime = 1;
	timeCnt = 100;

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

void GameScene::AddTile()
{
	vector<Tile*> randVec;
	for (int i = 0; i < 2; i++)
	{
		for (int calRand = 0; calRand < 4; calRand++)
		{
			for (int valueRand = 1; valueRand < 5; valueRand++)
			{
        Tile* tile = new Tile(valueRand, (CALC)calRand, OBJ_TYPE::NORMAL);
				randVec.push_back(tile);
        tile->SetSize({ 120, 120 });
			}
		}
	}

	//넣기
	while (!randVec.empty())
	{
		int value = rand() % randVec.size();
		Tile* temp = randVec[value];
		randVec.erase(randVec.begin() + value);
		nextTiles.push_back(temp);
	}
  
  
	

	cout << endl << "~~NextTilesList~~ " << nextTiles.size() << endl;
	for (int i = 0; i < nextTiles.size(); i++)
	{
		wcout << nextTiles[i]->ShowValue() << endl;
	}
	cout << "Fin" << endl;
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
	board->AddToBoardNoAddObject(nextTiles[0], vec,
		backBoard->data[(int)vec.y][(int)vec.x]
		->GetPos());
	nextTiles.erase(nextTiles.begin(), nextTiles.begin()+1);

	for (auto& tile : nextTiles) {
		tile->SetPos(tile->GetPos() - Vec2(0, 200));
	}
}

void GameScene::StageInit()
{
	cout << endl << "~~~~~~~~~~" << endl;
	cout << "STAGE Init" << endl;
	cout << "~~~~~~~~~~" << endl << endl;

	AddTile();

	gameState = GAME_STATE::PLAY;
	targetNum = 15;
}

bool GameScene::CheckTarget() { return mainTile->value == targetNum; }

void GameScene::FindTarget()
{
	targetNum = rand() % 15 + 1;
	if (rand() % 2 == 0) targetNum *= -1;

	cout << "Target : " << targetNum << endl;
}

