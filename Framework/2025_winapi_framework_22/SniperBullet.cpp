#include "pch.h"
#include "SceneManager.h"
#include "SniperBullet.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Texture.h"
#include "Collider.h"

SniperBullet::SniperBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"SniperBullet");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 15,15 });

	m_damage = 40;
	m_speed = 600;
}

SniperBullet::~SniperBullet()
{
}

void SniperBullet::Update()
{
	Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });
	if (isFlip == true)
	{
		m_angleValue += (38 * fDT);
	}
	else if (isFlip == false)
	{
		m_angleValue += (-38 * fDT);
	}
	BulletFlip();
}

void SniperBullet::BulletFlip()
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

void SniperBullet::Render(HDC _hdc)
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

void SniperBullet::BurstBullet()
{
}

void SniperBullet::Rotate()
{
}

void SniperBullet::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void SniperBullet::DestroyOther(Collider* _other)
{
}
