#include "pch.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "SceneManager.h"
#include <thread>


TestWeapon::TestWeapon()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");

	m_angle.x = 1.f;
	m_angle.y = 0.f;
	
}

TestWeapon::~TestWeapon()
{
}

void TestWeapon::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
		Shoot();

	if (GET_KEYDOWN(KEY_TYPE::Q))
	{
		if (m_angle.y == 0.f)
		{
			cout << "야ㅕ기디임마";
			m_angle.y = -0.5f;
		}
		else
		{
			m_angle.x = 0.3f;
			m_angle.y = -0.5f;
			float a = std::atan2(m_angle.y, m_angle.x);
			cout << a << endl;
		}
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

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height,
		RGB(255, 0, 255));
}

void TestWeapon::Shoot()
{
	TestBullet* proj = new TestBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	proj->SetDir(m_angle);


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);

	m_offsetPos.x -= 1.f;

	std::thread([this]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			m_offsetPos.y += 1.f;
		}).detach();

	
}
