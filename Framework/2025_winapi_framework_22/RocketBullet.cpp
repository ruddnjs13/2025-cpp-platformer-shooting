#include "pch.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "WindManager.h"
#include "Texture.h"
#include "Collider.h"
#include "SceneManager.h"
#include "RocketBullet.h"
#include "Bomb.h"

RocketBullet::RocketBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"RocketBullet");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 25,25 });

	m_damage = 15;
	m_speed = 500;
}

RocketBullet::~RocketBullet()
{
}

void RocketBullet::Update()
{
		m_speed + GET_SINGLE(WindManager)->m_windPower;
		Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });
		if (isFlip == true)
		{
			m_angleValue += (-38 * fDT);
		}
		else if (isFlip == false)
		{
			m_angleValue += (38 * fDT);
		}
		BulletFlip();
}

void RocketBullet::Render(HDC _hdc)
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

void RocketBullet::BurstBullet()
{
	Bomb* bomb = new Bomb;

	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	Vec2 angle = Vec2(0.f, 0.f);

	bomb->SetPos(pos);
	bomb->SetSize({ 30,30 });

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bomb, Layer::PROJECTILE);
}

void RocketBullet::Rotate()
{
}

void RocketBullet::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void RocketBullet::DestroyOther(Collider* _other)
{
}

void RocketBullet::BulletFlip()
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
