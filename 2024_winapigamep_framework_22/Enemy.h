#pragma once
#include "Object.h"
#include "Action.h"
class Enemy :
    public Object
{
public:
	Enemy();
	~Enemy();
public:
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	int m_hp;
};

