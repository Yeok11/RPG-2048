#pragma once
#include "Object.h"

class Tile : public Object
{
public:
	Tile()
	{
		value = 0;
		cal = CALC::PLUS;
		type = OBJ_TYPE::NONE;
	};
	Tile(int _value, CALCULATE _cal, OBJ_TYPE _type);
	~Tile();

	int value;
	OBJ_TYPE type;
	CALCULATE cal;
private:

public:
	std::string ShowValue();

private:
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
};

