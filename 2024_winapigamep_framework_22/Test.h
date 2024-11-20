#pragma once
#include "Object.h"
class Test : public Object
{
public:
    Test();
    ~Test() override;
public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
};

