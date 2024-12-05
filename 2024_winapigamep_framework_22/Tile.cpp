#include "pch.h"
#include "Tile.h"
#include "Text.h"
#include "Image.h"




Tile::Tile(int _value, CALCULATE _cal, OBJ_TYPE _type, bool _show)
{
	value = _value;
	cal = _cal;
	type = _type;

	SetSize({ 100, 100 });

	if (_show) 
	{
		Init();
	}
}

Tile::Tile()
{
	value = 0;
	cal = CALC::PLUS;
	type = OBJ_TYPE::NONE;
};

Tile::~Tile()
{
}



wstring Tile::ShowValue()
{
	if (this == nullptr) return L" 0";

	wstring mes;
	switch (cal)
	{
	case CALCULATE::PLUS:
		mes = L"+";
		break;
	case CALCULATE::MINUS:
		mes = L"-";
		break;
	case CALCULATE::MULTIPLY:
		mes = L"X";
		break;
	case CALCULATE::DIVIDE:
		mes = L"/";
		break;
	}

	mes += std::to_wstring(abs(value));

	return mes;
}

void Tile::Init()
{
	AddComponent<Image>();
	AddComponent<Text>();

	GetComponent<Image>()->TileLoadSetting(type, 3, 3);
	GetComponent<Text>()->SetFont(L"PFStardust.ttf", L"PF Stardust", 0, 0);

	ComponentInit(GetSize(), GetPos());

	if (type != OBJ_TYPE::EMPTY) {
		wstring number = ShowValue();
		GetComponent<Text>()->SetText(number);
	}
}

void Tile::Move()
{
	Vec2 pos = GetPos();
	SetPos({ pos.x + moveValue.x, pos.y + moveValue.y });
}

void Tile::Update()
{
}

void Tile::Render(HDC _hdc)
{
	if (type == OBJ_TYPE::NONE) return;

	GetComponent<Image>()->Render(_hdc);
	GetComponent<Text>()->Render(_hdc);
}
