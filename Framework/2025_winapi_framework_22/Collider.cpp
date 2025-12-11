#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "ResourceManager.h"
UINT Collider::m_nextID = 0;
Collider::Collider()
	: m_size{30.f,30.f}
	, m_updatedPos{0.f,0.f}
	, m_offsetPos{0.f,0.f}
	, m_ID(m_nextID++)
	, m_showDebug(false)
{

}
void Collider::LateUpdate()
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();
	m_updatedPos = pos + m_offsetPos;
}

void Collider::Render(HDC _hDC)
{
	PenType colorPen = PenType::GREEN;
	if (m_showDebug)
		colorPen = PenType::RED;
	GDISelector pen(_hDC, colorPen);
	GDISelector brush(_hDC, BrushType::HOLLOW);
	RECT_RENDER(_hDC, m_updatedPos.x, m_updatedPos.y,
		m_size.x, m_size.y);
}
void Collider::EnterCollision(Collider* _other)
{
	m_showDebug = true;
	m_isCol = true;
	GetOwner()->EnterCollision(_other);
	m_lateColMap[_other->GetID()] = _other;
}
void Collider::StayCollision(Collider* _other)
{
	m_isCol = true;
	GetOwner()->StayCollision(_other);
	m_lateColMap[_other->GetID()] = _other;
}
void Collider::ExitCollision(Collider* _other)
{
	m_showDebug = false;
	GetOwner()->ExitCollision(_other);
	
	m_lateColMap[_other->GetID()] = nullptr;
	m_lateColMap.erase(_other->GetID());
}
Collider::~Collider()
{
	
	for (auto& item : m_lateColMap)
	{
		if (item.second != nullptr)
		{
			item.second->ExitCollision(this);
		}
	}
	m_isCol = false;
	m_lateColMap.clear();
}

void Collider::Init()
{

}


