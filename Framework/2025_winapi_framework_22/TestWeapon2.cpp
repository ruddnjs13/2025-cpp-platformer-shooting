#include "pch.h"
#include "TestWeapon2.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "SceneManager.h"
#include <thread>

TestWeapon2::TestWeapon2()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Gun1");
}

TestWeapon2::~TestWeapon2()
{
}

void TestWeapon2::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::SPACE) )
		Shoot();
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

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height,
		RGB(255, 0, 255));
}

void TestWeapon2::Shoot()
{
	TestBullet* proj = new TestBullet;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	pos.y += 60.f;
	pos.x += 30.f;
	proj->SetPos(pos);
	proj->SetSize({ 20.f,20.f });
	proj->SetDir({18.f, 0.f });

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);

	Vec2 vec = GetOwner()->GetPos();

	vec.x -= 4.f;

	GetOwner()->SetPos(vec);

	m_offsetPos.x -= 1.f;

	std::thread([this]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			m_offsetPos.x += 1.f;
		}).detach();
	
}
