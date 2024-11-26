#include "pch.h"
#include "Tile.h"

Tile::Tile(int _value, CALCULATE _cal, OBJ_TYPE _type, bool _isVirtual = false)
{
	value = _value;
	cal = _cal;
	type = _type;
	isVirtual = _isVirtual;
}

Tile::~Tile()
{
}



void Tile::Update()
{
}

void Tile::Render(HDC _hdc)
{
}
