#pragma once
class Object;
class Component
{
public:
	Component();
	virtual ~Component();
public:
	virtual void Init(Vec2 _vSize, Vec2 _vOffsetPos);
	virtual void LateUpdate() abstract;
	virtual void Render(HDC _hdc) abstract;
public:
	void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
	const Vec2& GetSize() const { return m_vSize; }
	void SetOffSetPos(Vec2 _vOffsetPos)
	{
		m_vOffsetPos = _vOffsetPos;
	}
	const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
public:
	void SetOwner(Object* _owner) { m_pOwner = _owner; }
	Object* GetOwner() const { return m_pOwner; }
protected:
	Object* m_pOwner;
	Vec2 m_vSize;
	Vec2 m_vOffsetPos;
};

