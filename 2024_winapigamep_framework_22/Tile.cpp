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



std::string Tile::ShowValue()
{
	if (this == nullptr) return " 0";

	std::string mes;
	switch (cal)
	{
	case CALCULATE::PLUS:
		mes = "+";
		break;
	case CALCULATE::MINUS:
		mes = "-";
		break;
	case CALCULATE::MULTIPLY:
		mes = "X";
		break;
	case CALCULATE::DIVIDE:
		mes = "/";
		break;
	}

	mes += std::to_string(abs(value));

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
		std::string number = ShowValue();
		GetComponent<Text>()->SetText(wstring().assign(number.begin(), number.end()));
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
