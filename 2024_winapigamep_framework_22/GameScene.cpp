#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Lerp.h"
#include "TimeManager.h"
#include "GameScene.h"

GameScene::~GameScene()
{
	delete(board);
	delete(backBoard);
}

void GameScene::Init()
{
	srand((unsigned int)time(0));

	gameState = GAME_STATE::INIT;
	gameTime = 20;

	#pragma region Tile Render
	GET_SINGLE(ResourceManager)->TileInit(L"Button_empty.bmp", OBJ_TYPE::EMPTY);
	GET_SINGLE(ResourceManager)->TileInit(L"Button.bmp", OBJ_TYPE::MAIN);;
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Normal.bmp", OBJ_TYPE::NORMAL);
	GET_SINGLE(ResourceManager)->TileInit(L"Button_Stone.bmp", OBJ_TYPE::STONE);
	#pragma endregion

	#pragma region Sound
	GET_SINGLE(ResourceManager)->LoadSound(L"pop", L"Sound\\pop-268648.mp3", false);
	
	#pragma endregion

	#pragma region Board Setting
	board = new Board();
	backBoard = new Board();

	#pragma region AllTile Init
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			backBoard->data[i][j] = new Tile(0, CALC::PLUS, OBJ_TYPE::EMPTY);
			backBoard->data[i][j]->SetPos({ (SCREEN_WIDTH / 2) + (j - 2) * 100, 
				(SCREEN_HEIGHT / 2) + (i - 2) * 100 });
			AddObject(backBoard->data[i][j], LAYER::EMPTY_TILE);
		}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			board->data[i][j] = new Tile();
			AddObject(board->data[i][j], LAYER::OBJECT_TILE);
		}
#pragma endregion

	mainTile = new Tile(0, CALC::PLUS, OBJ_TYPE::MAIN);
	board->AddToBoard(mainTile, { 2,2 }, backBoard->data[2][2]->GetPos());

	#pragma region UI Setting
	
	UI* tilesImage = new UI();
	tilesImage->SetPos({ 1250, 300 });
	tilesImage->LoadAndSetting(L"BtnUI_UP", L"Texture\\back.bmp", 0.5f, 1.7f);
	tilesImage->ComponentInit(tilesImage->GetSize(), tilesImage->GetPos());
	AddObject(tilesImage, LAYER::EMPTY_TILE);

	UI* boardImg = new UI();
	boardImg->SetPos({ 595, 315 });
	boardImg->LoadAndSetting(L"BtnUI_UP", L"Texture\\back.bmp", 1.3f, 1.3f);
	boardImg->ComponentInit(boardImg->GetSize(), boardImg->GetPos());
	AddObject(boardImg, LAYER::EMPTY_TILE);

	UI* ntMes = new UI(false, true, false);
	ntMes->SetPos({ 1100, 30});
	ntMes->SetFont(L"Nt.ttf", L"DungGeunMo", 50, 90);
	ntMes->SetText(L"NEXT");
	ntMes->ComponentInit(ntMes->GetSize(), ntMes->GetPos());
	AddObject(ntMes, LAYER::UI);

	timeTxt = new UI(false, true, false);
	timeTxt->SetPos({ 50, 500 });
	timeTxt->SetFont(L"Nt.ttf", L"DungGeunMo", 30, 70);
	timeTxt->SetText(L"");
	timeTxt->ComponentInit(timeTxt->GetSize(), timeTxt->GetPos());
	AddObject(timeTxt, LAYER::UI);

	scoreTxt = new UI(false, true, false);
	scoreTxt->SetPos({ 620, 50 });
	scoreTxt->SetFont(L"Nt.ttf", L"DungGeunMo", 30, 70);
	SetScore(-1);
	scoreTxt->ComponentInit(scoreTxt->GetSize(), scoreTxt->GetPos());
	AddObject(scoreTxt, LAYER::UI);
	#pragma endregion


	targetTxt = new UI(false, true, false);
	targetTxt->SetPos({ 50, 30 });
	targetTxt->SetFont(L"Nt.ttf", L"DungGeunMo", 30, 70);
	targetTxt->SetText(L" MAKE : " + targetNum);
	AddObject(targetTxt, LAYER::UI);

	targetNum = 99;
	gameState = GAME_STATE::INIT;
}

void GameScene::Update()
{
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

	if (nextTiles.size() <= 5)
	{
		AddTile();
	}


	if (gameState == GAME_STATE::MOVE)
	{
		if (timeCnt > 0)
		{
			if (timeCnt > moveTime)//if leo can't make Move
			{
				timeCnt -= 0.01f;

				for (int x = 0; x < 5; x++)
					for (int j = 0; j < 5; j++) board->data[x][j]->Move();
			}
			moveTime -= fDT;
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
		FindTarget();
		StageInit();
		SetScore();
		return;
	}
	
	else if (gameState == GAME_STATE::PLAY)
	{
		gameTime -= fDT;

		if (GET_KEYDOWN(KEY_TYPE::W)) Move({ 0, -1 });
		else if (GET_KEYDOWN(KEY_TYPE::A)) Move({ -1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::S)) Move({ 0, 1 });
		else if (GET_KEYDOWN(KEY_TYPE::D)) Move({ 1, 0 });
		else if (GET_KEYDOWN(KEY_TYPE::E)) AddTileRandom();
	}
	float p = round(gameTime * 10) / 10;
	wstring timeMes = std::to_wstring((int)gameTime) + L"." + std::to_wstring((int)(gameTime * 10) % 10);
	timeTxt->SetText(timeMes);
	if (gameTime < 0) { 
		GET_SINGLE(SceneManager)->LoadScene(L"GameOverScene");
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

	moveTime = 1;
	timeCnt = 10;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board->data[i][j]->moveValue = 
				Lerp(board->data[i][j]->GetPos(), 
				backBoard->data[i][j]->GetPos(), moveTime / timeCnt);
		}
	}
	GET_SINGLE(ResourceManager)->Play(L"pop");
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
				randVec.push_back(new Tile(valueRand, (CALC)calRand, OBJ_TYPE::NORMAL));
			}
		}
	}

	//넣기
	while (!randVec.empty())
	{
		int value = rand() % randVec.size();
		Tile* temp = randVec[value];
		temp->SetPos({1095, 175 + (int)nextTiles.size() * 115});
		randVec.erase(randVec.begin() + value);
		nextTiles.push_back(temp);
		AddObject(temp, LAYER::OBJECT_TILE);
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
		backBoard->data[(int)vec.y][(int)vec.x]->GetPos());
	nextTiles.erase(nextTiles.begin());

	for (auto& tile : nextTiles) {
		tile->SetPos(tile->GetPos() - Vec2(0, 115));
	}
}

void GameScene::StageInit()
{
	cout << endl << "~~~~~~~~~~" << endl;
	cout << "STAGE Init" << endl;
	cout << "~~~~~~~~~~" << endl << endl;

	gameState = GAME_STATE::PLAY;
}

bool GameScene::CheckTarget() { return mainTile->value == targetNum; }

void GameScene::FindTarget()
{
re:
	int randomTarget = rand() % 10 + 1;
	if (rand() % 2 == 0) randomTarget *= -1;

	if (randomTarget == targetNum) goto re;

	targetNum = randomTarget;

	cout << "Target : " << targetNum << endl;

	gameTime += 5 - (score / 20);

	wstring txt = L"MAKE : ";
	txt += std::to_wstring(targetNum);
	targetTxt->SetText(txt);
}

