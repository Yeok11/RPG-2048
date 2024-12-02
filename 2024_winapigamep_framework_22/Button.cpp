#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "GDISelector.h"

Button::Button()
{
}

Button::~Button()
{
	act.Clear();
}

void Button::LateUpdate()
{
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON) && IsMouseOnButton())
	{
		OnClick();
	}
}

void Button::Render(HDC _hdc)
{
	/*PEN_TYPE ePen = PEN_TYPE::GREEN;
	GDISelector pen(_hdc, ePen);
	GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(_hdc, m_vOffsetPos.x, m_vOffsetPos.y,
		m_vSize.x, m_vSize.y);*/
}

void Button::OnClick()
{
	act.Invoke();
}

void Button::AddListener(std::function<void()> listen)
{
	act += listen;
}
