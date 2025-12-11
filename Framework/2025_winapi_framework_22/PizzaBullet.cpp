#include "pch.h"
#include "SceneManager.h"
#include "WindManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "PizzaBullet.h"

PizzaBullet::PizzaBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Pizza");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 15,15 });

	m_damage = -20;

	m_speed = 150;
}

PizzaBullet::~PizzaBullet()
{
}

void PizzaBullet::Update()
{
	m_speed + GET_SINGLE(WindManager)->m_windPower;
	Translate({0 * m_speed * fDT, -1 * m_speed * fDT });



	destoryTime += 1 * fDT;

	if (destoryTime >= 7)
	{
		DestoyThis();
	}

}

void PizzaBullet::Render(HDC _hdc)
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

void PizzaBullet::BurstBullet()
{
}

void PizzaBullet::Rotate()
{
}

void PizzaBullet::AfterEffect()
{
	PLAY_SOUND(L"PizzaGunHitSFX");
}

void PizzaBullet::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void PizzaBullet::DestroyOther(Collider* _other)
{
	GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
}

void PizzaBullet::BulletFlip()
{
	if (isFlip && m_playerCount == 1)
	{
		m_pTex->SetFlipped(true);
	}
	else if (isFlip == false && m_playerCount == 1)
	{
		m_pTex->SetFlipped(false);
	}

	if (isFlip && m_playerCount == 2)
	{
		m_pTex->SetFlipped(true);
	}
	else if (isFlip == false && m_playerCount == 2)
	{
		m_pTex->SetFlipped(false);
	}
}
