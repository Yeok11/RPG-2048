#pragma once
#include "Component.h"
#include "InputManager.h"

class Button :
    public Component
{
public:
	Button();
	~Button();
public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
	void OnClick();
    void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
    const Vec2& GetSize() const { return m_vSize; }
    void SetOffSetPos(Vec2 _vOffsetPos)
    {
        m_vOffsetPos = _vOffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
    bool IsMouseOnButton() 
    {
        return MOUSE_ON_OBJECT(m_vSize, m_vOffsetPos);
    }
private:
    Vec2 m_vSize;
    Vec2 m_vOffsetPos;
};

