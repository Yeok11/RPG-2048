#pragma once
#include "Object.h"

class Tile : public Object
{
public:
	Tile();
	Tile(int _value, CALCULATE _cal, OBJ_TYPE _type, bool _show = true);
	~Tile();

	int value;
	OBJ_TYPE type;
	CALCULATE cal;
private:

public:
	std::string ShowValue();

	void Init();

private:
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
};

