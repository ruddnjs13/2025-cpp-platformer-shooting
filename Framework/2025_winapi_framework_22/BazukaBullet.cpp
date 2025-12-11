#include "pch.h"
#include "Collider.h"
#include "Texture.h"
#include "WindManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "BazukaBullet.h"
#include "Bomb.h"

BazukaBullet::BazukaBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"BazookaBullet");
	auto* col = AddComponent<Collider>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 25,25 });
	m_damage = 40;
	m_speed = 200;
}

BazukaBullet::~BazukaBullet()
{
}

void BazukaBullet::Update()
{
	m_speed + GET_SINGLE(WindManager)->m_windPower;
	Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });
	BulletFlip();

	destoryTime += 1 * fDT;

	if (destoryTime >= 7)
	{
		DestoyThis();
	}
}

void BazukaBullet::Render(HDC _hdc)
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

void BazukaBullet::BurstBullet()
{
	Bomb* bomb = new Bomb;

	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	Vec2 angle = Vec2(0.f, 0.f);

	bomb->SetPos(pos);
	bomb->SetSize({ 40,40 });

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bomb, Layer::PROJECTILE);
}

void BazukaBullet::Rotate()
{
}

void BazukaBullet::DestoyThis()
{
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void BazukaBullet::DestroyOther(Collider* _other)
{
}

void BazukaBullet::BulletFlip()
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

