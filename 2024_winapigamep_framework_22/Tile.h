#pragma once
#include "Object.h"

class GameScene;
class Tile : public Object
{
public:
	Tile();
	Tile(int _value, CALCULATE _cal, OBJ_TYPE _type, bool _show = true);
	~Tile();

	int value;
	OBJ_TYPE type;
	CALCULATE cal;
	bool merge = true;
private:

public:
	std::string ShowValue();

	void Init();
	void Move();
	void Calculate(Tile * _tile)
	{
		switch (_tile->cal)
		{
		case CALC::PLUS:
			value += _tile->value;
			break;
		case CALC::MINUS:
			value -= _tile->value;
			break;
		case CALC::MULTIPLY:
			value *= _tile->value;
			break;
		case CALC::DIVIDE:
			value /= _tile->value;
			break;
		}
	}

private:
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
};

