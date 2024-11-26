#include "pch.h"
#include "Tile.h"

Tile::Tile(int _value, CALCULATE _cal, OBJ_TYPE _type)
{
	value = _value;
	cal = _cal;
	type = _type;
}

void Tile::Update()
{
}

void Tile::Render(HDC _hdc)
{
}
