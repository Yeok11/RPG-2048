#pragma once
#include "Component.h"
#include "InputManager.h"
#include "Action.h"

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
    void AddListener(std::function<void()> listen);

    bool IsMouseOnButton() 
    {
        return MOUSE_ON_OBJECT(m_vSize, m_vOffsetPos);
    }
public:
    Action act;
};

