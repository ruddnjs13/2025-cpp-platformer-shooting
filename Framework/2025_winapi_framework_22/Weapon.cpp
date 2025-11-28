#include "pch.h"
#include "Weapon.h"
#include "ResourceManager.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::SetRotation(Vec2 _angle)
{
	
}

void Weapon::SetShootAngle(float angle)
{
	float radian = angle / 57.2958f;
	
	float y = tan(radian);

	m_angle.y = -y;
}

