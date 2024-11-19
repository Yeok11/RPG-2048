#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "EventManager.h"
#include "Button.h"
#include "Image.h"


Enemy::Enemy()
	: m_hp(5)
{
	//this->AddComponent<Collider>();
	this->AddComponent<Image>();
	GetComponent<Image>()->Init(GetSize(), GetPos());
	GetComponent<Image>()->LoadAndSetting(L"UI", L"Texture\\Button1.bmp", 10, 10);
}

Enemy::Enemy(Vec2 _size, Vec2 _pos)
	:m_hp(5)
{
	SetPos(_pos);
	SetSize(_size);
	this->AddComponent<Image>();
	GetComponent<Image>()->Init(GetSize(), GetPos());
	GetComponent<Image>()->LoadAndSetting(L"UI", L"Texture\\Button1.bmp", 10, 10);
}


Enemy::~Enemy()
{
	
}

void Enemy::Update()
{
}

void Enemy::LateUpdate()
{
}



void Enemy::Render(HDC _hdc)
{	
	//HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	//HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, brush);
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	ComponentRender(_hdc);
	//SelectObject(_hdc, oldbrush); 
	//DeleteObject(brush);
}

void Enemy::EnterCollision(Collider* _other)
{
	/*std::cout << "Enter" << std::endl;
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		m_hp -= 1;
		if(m_hp <=0)
			GET_SINGLE(EventManager)->DeleteObject(this);
	}*/
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	std::cout << "Exit" << std::endl;
}
