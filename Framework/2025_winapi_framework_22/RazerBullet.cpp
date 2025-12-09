#include "pch.h"
#include "WindManager.h"
#include "ResourceManager.h"
#include "SceneManager.h";
#include "Rigidbody.h"
#include "Texture.h"
#include "Collider.h"
#include "RazerBullet.h"

RazerBullet::RazerBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Gun1Bullet");
	auto* col = AddComponent<Collider>();
	AddComponent<Rigidbody>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
	col->SetSize({ 15,15 });
}

RazerBullet::~RazerBullet()
{
}

void RazerBullet::Update()
{
	m_speed + GET_SINGLE(WindManager)->m_windPower;
	Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });
}

void RazerBullet::Render(HDC _hdc)
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

void RazerBullet::BurstBullet()
{
}

void RazerBullet::Rotate()
{
}

void RazerBullet::DestoyThis()
{

}

void RazerBullet::DestroyOther(Collider* _other)
{
	GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
}

