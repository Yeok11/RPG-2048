#include "pch.h"
#include "MouseDetectObject.h"
#include "InputManager.h"

MouseDetectObject::MouseDetectObject()
	:MouseEnter()
	,MouseExit()
	,mouseDetected(false)
{
}

MouseDetectObject::~MouseDetectObject()
{
}

void MouseDetectObject::Update()
{
	if (!mouseDetected && MOUSE_ON_OBJECT(GetSize(), GetPos())) {
		OnMouseEnter();
	}
	else if (mouseDetected && !MOUSE_ON_OBJECT(GetSize(), GetPos())) {
		OnMouseExit();
	}
}

void MouseDetectObject::Render(HDC _hdc)
{
}

void MouseDetectObject::OnMouseEnter()
{
	MouseEnter.Invoke();
	mouseDetected = true;
}

void MouseDetectObject::OnMouseExit()
{
	MouseExit.Invoke();
	mouseDetected = false;
}
