#include "pch.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "WeaponTrajectory.h"
#include "SceneManager.h"
#include <thread>


TestWeapon::TestWeapon()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AK47");

	m_weaponTrajectory = AddComponent<WeaponTrajectory>();

	SetShootAngle(m_angleValue);
}



TestWeapon::~TestWeapon()
{
	m_weaponTrajectory->DestoryTrajectory();
}

void TestWeapon::WeaponFlip()
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
		StartAngle(-1, -50);
		m_pTex->SetFlipped(true);
	}
	else if (isFlip == false && m_playerCount == 2)
	{
		m_pTex->SetFlipped(false);
		StartAngle(1, 10);
	}
}

void TestWeapon::Update()
{
	WeaponFlip();

	if (m_ismultiShoot == true)
	{
		m_waitTime += fDT;

		if (m_waitTime >= 0.3)
		{
			PLAY_SOUND(L"AK47FireSFX");
			MakeBullet();
		}
	}

	if (isFlip == true)
	{
		float radius = sqrtf(10 * 10 + m_offsetPos.y * m_offsetPos.y);

		float radian = m_angleValue * (PI / 180.0f);

		float x = cosf(radian) * radius;
		float y = -sinf(radian) * radius;

		x *= 5;
		x = -x;


		m_offsetPos = Vec2(x, y);

	}
	else if (isFlip == false)
	{
		float radius = sqrtf(m_offsetPos.x * m_offsetPos.x + m_offsetPos.y * m_offsetPos.y);
		float radian = m_angleValue * (PI / 180.0f);

		float x = cosf(radian) * radius;
		float y = -sinf(radian) * radius;

		m_offsetPos = Vec2(x, y);
	}


	if (GET_KEYDOWN(KEY_TYPE::F) && isShoot == true && m_playerCount == 1)
		Shoot();

	if (GET_KEYDOWN(KEY_TYPE::ENTER) && isShoot == true && m_playerCount == 2)
	{
		Shoot();
	}



	if (GET_KEY(KEY_TYPE::W) && isRotation == true && m_playerCount == 1)
	{

		isRotation = false;

		m_angleValue += 0.5f;
		if (m_angleValue >= 75)
		{
			m_angleValue = 75;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;

		SetShootAngle(m_angleValue);

				isRotation = true;

	}

	if (GET_KEY(KEY_TYPE::UP) && isRotation == true && m_playerCount == 2)
	{
		isRotation = false;

		m_angleValue += 0.5f;

		if (m_angleValue >= 75)
		{
			m_angleValue = 75;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;
		SetShootAngle(m_angleValue);

				isRotation = true;

	}

	if (GET_KEY(KEY_TYPE::S) && isRotation == true && m_playerCount == 1)
	{

		isRotation = false;

		m_angleValue -= 0.5f;

		if (m_angleValue <= -45)
		{
			m_angleValue = -45;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;


		SetShootAngle(m_angleValue);



		isRotation = true;

	}

	if (GET_KEY(KEY_TYPE::DOWN) && isRotation && m_playerCount == 2)
	{
		isRotation = false;
		m_angleValue -= 0.5f;

		if (m_angleValue <= -45)
		{
			m_angleValue = -45;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;

		SetShootAngle(m_angleValue);

				isRotation = true;

	}
}

void TestWeapon::Rotate()
{
}

void TestWeapon::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	HDC texDC = m_pTex->GetRotateTextureDC(m_angleValue, 0, 0, width, height);


	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, texDC
		, 0, 0, width, height,
		RGB(255, 0, 255));

}

void TestWeapon::Shoot()
{
	isShoot = false;
	isRotation = false;
	m_ismultiShoot = true;
}

void TestWeapon::MakeBullet()
{
	if (m_bulletCnt >= 2)
	{
		m_bulletCnt = 0;
		m_ismultiShoot = false;
		m_waitTime = 0;
	}

	m_waitTime = 0;

	m_bulletCnt += 1;
	TestBullet* proj = new TestBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	if (isFlip == false)
	{
		pos.y += 5;
		pos.x += 6;
	}
	else if (isFlip == true)
	{
		pos.y += 5;
		pos.x -= 8;
	}
	proj->SetPos(pos);
	proj->SetSize({ 15.f,15.f });
	proj->SetDir(m_angle);
	proj->SetAngleValue(m_angleValue);
	proj->SetFlip(isFlip);
	proj->SetPlayer(m_playerCount);


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);
}
