#include "pch.h"
#include "TestBullet.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Collider.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "TurnManager.h"

TestBullet::TestBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
}

TestBullet::~TestBullet()
{
	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
}

void TestBullet::Update()
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
}

void TestBullet::BurstBullet()
{

}

void TestBullet::Rotate()
{

}
