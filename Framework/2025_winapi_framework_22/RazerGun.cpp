#include "pch.h"
#include "InputManager.h"
#include "RazerGun.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Texture.h"	
#include "RazerBullet.h"
#include <thread>

RazerGun::RazerGun()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"RazerGun");


	SetShootAngle(m_angleValue);
}

RazerGun::~RazerGun()
{
}

void RazerGun::Update()
{
	WeaponFlip();

	if (GET_KEYDOWN(KEY_TYPE::RSHIFT) && isShoot == true && m_playerCount == 1)
		Shoot();

	if (GET_KEYDOWN(KEY_TYPE::ENTER) && isShoot == true && m_playerCount == 2)
	{
		Shoot();
	}


	if (GET_KEY(KEY_TYPE::W) && isRotation == true && m_playerCount == 1)
	{
		cout << m_playerCount << endl;

		isRotation = false;

		m_angleValue += 1;
		if (m_angleValue >= 75)
		{
			m_angleValue = 75;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;

		SetShootAngle(m_angleValue);

		std::thread([this]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				isRotation = true;
			}).detach();

	}

	if (GET_KEY(KEY_TYPE::UP) && isRotation == true && m_playerCount == 2)
	{
		isRotation = false;

		m_angleValue += 1;

		if (m_angleValue >= 75)
		{
			m_angleValue = 75;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;
		SetShootAngle(m_angleValue);


		std::thread([this]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				isRotation = true;
			}).detach();

	}

	if (GET_KEY(KEY_TYPE::S) && isRotation == true && m_playerCount == 1)
	{

		isRotation = false;

		m_angleValue -= 1;

		if (m_angleValue <= -45)
		{
			m_angleValue = -45;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;


		SetShootAngle(m_angleValue);


		std::thread([this]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				isRotation = true;
			}).detach();

	}

	if (GET_KEY(KEY_TYPE::DOWN) && isRotation && m_playerCount == 2)
	{
		isRotation = false;
		m_angleValue -= 1;

		if (m_angleValue <= -45)
		{
			m_angleValue = -45;
		}

		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;

		SetShootAngle(m_angleValue);

		std::thread([this]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				isRotation = true;
			}).detach();

	}
}

void RazerGun::Render(HDC _hdc)
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

void RazerGun::Shoot()
{
	isShoot = false;

	RazerBullet* proj = new RazerBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	if (m_playerCount == 1)
	{
		pos.y -= 7.f;
		pos.x += 30.f;
	}
	else if (m_playerCount == 2)
	{
		pos.y -= 7.f;
		pos.x -= 40.f;
	}
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	proj->SetDir(m_angle);
	proj->SetAngleValue(m_angleValue);
	proj->SetFlip(isFlip);
	proj->SetPlayer(m_playerCount);


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);
}

void RazerGun::WeaponFlip()
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
