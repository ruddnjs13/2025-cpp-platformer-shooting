#include "pch.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "Nail.h"
#include "WeaponTrajectory.h"
#include "SceneManager.h"
#include "Nailgun.h"
#include <thread>

Nailgun::Nailgun()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"NailGun");

	m_weaponTrajectory = AddComponent<WeaponTrajectory>();


	SetShootAngle(m_angleValue);
}

Nailgun::~Nailgun()
{
	m_weaponTrajectory->DestoryTrajectory();
}

void Nailgun::Shoot()
{
	isShoot = false;
	Nail* proj = new Nail;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	if (m_playerCount == 1)
	{
		pos.y += 10.f;
		pos.x += 30.f;
	}
	else if (m_playerCount == 2)
	{
		pos.y -= 10.f;
		pos.x -= 30.f;
	}
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	proj->SetDir(m_angle);


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);
}
void Nailgun::WeaponFlip()
{
	if (isFlip && m_playerCount == 1)
	{
		m_pTex->SetFlipped(true);
		StartAngle(-1, -50);
	}
	else if (isFlip == false && m_playerCount == 1)
	{
		m_pTex->SetFlipped(false);
		StartAngle(1, 10);
	}

	if (isFlip && m_playerCount == 2)
	{
		m_pTex->SetFlipped(false);
		StartAngle(-1, -50);
	}
	else if (isFlip == false && m_playerCount == 2)
	{
		StartAngle(1, 10);
		m_pTex->SetFlipped(true);
	}
}

void Nailgun::Update()
{
	WeaponFlip();

	if (GET_KEYDOWN(KEY_TYPE::RSHIFT) && isShoot)
		Shoot();

	if (GET_KEY(KEY_TYPE::W) && isRotation == true)
	{
		cout << m_playerCount << endl;

		isRotation = false;
		if (m_playerCount == 1)
		{
			m_angleValue += 5;
			if (m_angleValue >= 75)
			{
				m_angleValue = 75;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;

			//pos.y + 10.f;
			//pos.x + 30.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue, m_angle, pos, { 20.f,20.f }, GetOwner(), this, isFlip);

			SetShootAngle(m_angleValue);
		}
		else if (m_playerCount == 2)
		{
			cout << "2" << endl;

			m_angleValue -= 5;

			if (m_angleValue <= -75)
			{
				m_angleValue = -75;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue, m_angle, pos, { 20.f,20.f }, GetOwner(), this, isFlip);

			SetShootAngle(-m_angleValue);
		}
	}

	if (GET_KEY(KEY_TYPE::S) && isRotation == true)
	{
		cout << m_playerCount << endl;

		isRotation = false;
		if (m_playerCount == 1)
		{
			m_angleValue -= 5;
			if (m_angleValue <= 0)
			{
				m_angleValue = 0;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue, m_angle, pos, { 20.f,20.f }, GetOwner(), this, isFlip);

			SetShootAngle(m_angleValue);
		}
		else if (m_playerCount == 2)
		{
			cout << "2" << endl;

			m_angleValue += 5;
			if (m_angleValue >= 0)
			{
				m_angleValue = 0;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue, m_angle, pos, { 20.f,20.f }, GetOwner(), this, isFlip);

			SetShootAngle(-m_angleValue);
		}
	}
}

void Nailgun::Render(HDC _hdc)
{
}
