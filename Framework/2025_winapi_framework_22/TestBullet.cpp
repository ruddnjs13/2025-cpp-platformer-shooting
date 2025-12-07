#include "pch.h"
#include "TestBullet.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Collider.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "TurnManager.h"
#include "InputManager.h"
#include "Rigidbody.h"
#include "Bomb.h"

TestBullet::TestBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Gun1Bullet");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
}

TestBullet::~TestBullet()
{
}


void TestBullet::Render(HDC _hdc)
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

	ComponentRender(_hdc);
}

void TestBullet::Update()
{
	Translate({ m_dir.x * 500.f * fDT, m_dir.y * 500.f * fDT });
}

void TestBullet::BurstBullet()
{
	Bomb* proj = new Bomb;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;

	proj->SetPos(pos);
	proj->SetSize({ 70.f,70.f });

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::Boom);
}


void TestBullet::Rotate()
{

}
