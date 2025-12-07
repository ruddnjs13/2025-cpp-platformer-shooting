#include "pch.h"
#include "Weapon.h"
#include "Texture.h"
#include "ResourceManager.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::Update()
{
}

void Weapon::Render(HDC _hdc)
{
}


void Weapon::SetRotation(Vec2 _angle)
{
	
}

void Weapon::StartAngle(float x, float shootPosx)
{
	m_offsetPos.x = shootPosx;
	m_angle.x = x;
}

void Weapon::SetAngleToPositon()
{
	m_offsetPos.y -= 1.f;
	m_offsetPos.x -= 0.5f;
}

void Weapon::SetAngleToPosition2()
{
	m_offsetPos.y -= 1.f;
	m_offsetPos.x += 0.5f;
}

void Weapon::SetShootAngle(float angle)
{
	float radian = angle / 57.2958f;
	
	float y = tan(radian);

	m_angle.y = -y;
}

void Weapon::SetPlayerCount(int _playerNum)
{
	if (_playerNum != 1 && _playerNum != 2)
		return;

	if (_playerNum == 1)
	{
		m_playerCount = _playerNum;
		StartAngle(1, 10);
	}
	else if(_playerNum ==2)
	{
		m_playerCount = _playerNum;
		StartAngle(-1,-50);
	}

}



