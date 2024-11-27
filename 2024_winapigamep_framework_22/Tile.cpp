#include "pch.h"
#include "Tile.h"


Tile::Tile(int _value, CALCULATE _cal, OBJ_TYPE _type)
{
	value = _value;
	cal = _cal;
	type = _type;

	AddComponent<Image>();

	GetComponent<Image>()->TileLoadSetting(type, 1, 1);
	
}

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

	mes += std::to_string(value);

	return mes;
}

void Tile::Update()
{
}

void Tile::Render(HDC _hdc)
{
	GetComponent<Image>()->Render(_hdc);
}
