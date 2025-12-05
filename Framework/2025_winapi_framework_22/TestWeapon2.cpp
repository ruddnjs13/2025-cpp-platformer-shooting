#include "pch.h"
#include "TestWeapon2.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "SceneManager.h"
#include "Collider.h"
#include "Animator.h"
#include "WeaponTrajectory.h";
#include <thread>

TestWeapon2::TestWeapon2()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Gun1");
	m_weaponTrajectory = AddComponent<WeaponTrajectory>();

	m_angle.x = 1.f;
	m_angle.y = 0.f;
}

TestWeapon2::~TestWeapon2()
{
	m_weaponTrajectory->DestoryTrajectory();
}

void TestWeapon2::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::LSHIFT) )
		Shoot();

	if (GET_KEYDOWN(KEY_TYPE::Q) && isRotation == true)
	{
		isRotation = false;

		if (m_playerCount == 1)
		{
			m_angleValue += 5;
			if (m_angleValue >= 85)
			{
				m_angleValue = 85;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;

			pos.y += 10.f;
			pos.x += 30.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue,m_angle, pos, { 20.f,20.f }, GetOwner(), this);

			SetShootAngle(m_angleValue);
		}
		else
		{
			m_angleValue += 5;
			if (m_angleValue >= 85)
			{
				m_angleValue = 85;
			}

			Vec2 pos = GetPos();
			pos.y -= GetSize().y / 2.f;

			pos.y += 10.f;
			pos.x += 30.f;


			m_weaponTrajectory->ShowTrajectory(m_angleValue,m_angle, pos, { 20.f,20.f }, GetOwner(), this);

			SetShootAngle(m_angleValue);
		}
	}
}

void TestWeapon2::Rotate()
{
}

void TestWeapon2::Render(HDC _hdc)
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

	ComponentRender(_hdc);
}

void TestWeapon2::Shoot()
{

	TestBullet* proj = new TestBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	pos.y += 10.f;
	pos.x += 30.f;
	proj->SetPos(pos);
	proj->SetSize({ 20.f,20.f });
	proj->SetDir(m_angle);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);

	//m_offsetPos.x -= 1.f;
	//
	//std::thread([this]()
	//	{
	//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//		m_offsetPos.x += 1.f;
	//	}).detach();
}
