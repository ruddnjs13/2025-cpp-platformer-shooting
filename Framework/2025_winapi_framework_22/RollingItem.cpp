#include "pch.h"
#include "RollingItem.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Rigidbody.h"

RollingItem::RollingItem()
{
}

RollingItem::~RollingItem()
{

}

void RollingItem::Update()
{
	Translate({ 0 * speed * fDT, 1 * speed * fDT });
}

void RollingItem::Render(HDC _hdc)
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
void RollingItem::SetDownSpeed(float _speed)
{
	speed = _speed;
}

void RollingItem::SetTexture(wstring _textureName)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(_textureName);
}
