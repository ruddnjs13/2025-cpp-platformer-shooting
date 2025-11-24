#include "pch.h"
#include "TestWeapon2.h"
#include "TestWeapon.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Texture.h"
#include "TestBullet.h"
#include "SceneManager.h"

TestWeapon2::TestWeapon2()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
}

TestWeapon2::~TestWeapon2()
{
}

void TestWeapon2::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
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
	Projectile* proj = new Projectile;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	proj->SetDir({ 0.f, -1.f });
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);
}
