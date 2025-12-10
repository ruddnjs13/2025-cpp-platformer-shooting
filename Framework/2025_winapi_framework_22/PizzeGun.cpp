#include "pch.h"
#include "PizzeGun.h"
#include "PizzaBullet.h"
#include "InputManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <thread>

PizzeGun::PizzeGun()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PizzaGun");


	SetShootAngle(m_angleValue);
}

PizzeGun::~PizzeGun()
{

}

void PizzeGun::Update()
{
	WeaponFlip();

	if (GET_KEYDOWN(KEY_TYPE::RSHIFT) && isShoot == true && m_playerCount == 1)
		Shoot();

	if (GET_KEYDOWN(KEY_TYPE::ENTER) && isShoot == true && m_playerCount == 2)
	{
		Shoot();
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


	if (GET_KEY(KEY_TYPE::W) && isRotation == true && m_playerCount == 1)
	{
		cout << m_playerCount << endl;

		isRotation = false;

		m_angleValue += 1;
		if (m_angleValue >= 90)
		{
			m_angleValue = 90;
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

		if (m_angleValue >= 90)
		{
			m_angleValue = 90;
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

void PizzeGun::Render(HDC _hdc)
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

void PizzeGun::Shoot()
{
	isShoot = false;

	PizzaBullet* proj = new PizzaBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;

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

void PizzeGun::WeaponFlip()
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
