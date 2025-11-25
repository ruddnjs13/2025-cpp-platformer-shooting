#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() 
	: m_angle(0.f)
	, m_dir(1.f, 1.f)
	, m_damage(0.f)
	, m_speed(0.f)
{
}

Bullet::~Bullet()
{
}
