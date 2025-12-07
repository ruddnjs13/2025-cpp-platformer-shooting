#include "pch.h"
#include "Health.h"

Health::Health()
{
}

Health::~Health()
{
}

void Health::Init()
{
}

void Health::LateUpdate()
{
}

void Health::Render(HDC hDC)
{
}

void Health::TakeDamage(int damage)
{
	m_health -= damage; 
	
	if (m_health < 0)
	{
		m_health = 0;
		m_isDead = true;
	}
	OnHealthChanged.Invoke(m_health);
}
