#pragma once
#include "Object.h"
class Tile : public Object
{
	public:
		Tile() {}
		Tile(int _value, CALCULATE _cal)
		{
			value = _value;
			cal = _cal;
		}
		int value;
		CALCULATE cal;

		// Object을(를) 통해 상속됨
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
};

