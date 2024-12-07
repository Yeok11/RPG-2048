#pragma once
#include "Object.h"
#include "Action.h"

class MouseDetectObject :
    public Object
{
public:
    MouseDetectObject();
    ~MouseDetectObject() override;
public:
    void Update() override;
    void Render(HDC _hdc) override;

    void OnMouseEnter();
    void OnMouseExit();
public:
    Action MouseEnter;
    Action MouseExit;
private:
    bool mouseDetected;
};

