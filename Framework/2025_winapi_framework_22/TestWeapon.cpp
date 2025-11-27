#include "pch.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "SceneManager.h"

TestWeapon::TestWeapon()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Plane");
	
}

TestWeapon::~TestWeapon()
{
}

void TestWeapon::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
		Shoot();

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
	proj->SetDir({ 0.f, 1.f });


	

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);
}
