#pragma once
#include "Object.h"
class Tile : public Object
{
public:
		Tile() {}
		Tile(int _value, CALCULATE _cal, OBJ_TYPE _type, bool _isVirtual = false);
		~Tile();

private:
		int value;
		CALCULATE cal;
		OBJ_TYPE type;
		bool isVirtual;

		// Object��(��) ���� ��ӵ�
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
};

