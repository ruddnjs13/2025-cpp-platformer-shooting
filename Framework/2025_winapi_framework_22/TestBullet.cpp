#include "pch.h"
#include "TestBullet.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Collider.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "TurnManager.h"
#include "WindManager.h"
#include "InputManager.h"
#include "Rigidbody.h"
#include "Bomb.h"

TestBullet::TestBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet1");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 20,20 });
	m_angle = 15;
	m_speed = 500;
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

void TestBullet::BulletFlip()
{
	if (isFlip)
	{
		m_pTex->SetFlipped(true);
	}
	else if (isFlip == false )
	{
		m_pTex->SetFlipped(false);
	}
}

void TestBullet::Update()
{
	m_speed + GET_SINGLE(WindManager)->m_windPower;
	Translate({ m_dir.x * m_speed* fDT, m_dir.y * m_speed * fDT });
	BulletFlip();

	if (isFlip == true)
	{
		m_angleValue += (38 * fDT);
	}
	else if (isFlip == false)
	{
		m_angleValue += (-38 * fDT);
	}
}

void TestBullet::BurstBullet()
{
	
}


void TestBullet::Rotate()
{

}

void TestBullet::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void TestBullet::DestroyOther(Collider* _other)
{
}
