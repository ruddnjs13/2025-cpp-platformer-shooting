#include "pch.h"
#include "Collider.h"
#include "Texture.h"
#include "WindManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Nail.h"
#include <thread>

Nail::Nail()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Nail");
	auto* col = AddComponent<Collider>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 15,15 });
	m_damage = 20;
	m_speed = 600;
}

Nail::~Nail()
{
}

void Nail::Update()
{         
	Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });
}

void Nail::Render(HDC _hdc)
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

void Nail::BurstBullet()
{
}

void Nail::Rotate()
{
}

void Nail::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void Nail::DestroyOther(Collider* _other)
{
}

void Nail::BulletFlip()
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

