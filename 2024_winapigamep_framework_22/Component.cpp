#include "pch.h"
#include "Component.h"

Component::Component()
	: m_pOwner(nullptr)
{

}

Component::~Component()
{

}

void Component::Init(Vec2 _vSize, Vec2 _vOffsetPos)
{
	m_vSize = _vSize;
	m_vOffsetPos = _vOffsetPos;
}
