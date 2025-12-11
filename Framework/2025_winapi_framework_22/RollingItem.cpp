#include "pch.h"
#include "RollingItem.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "Collider.h";

RollingItem::RollingItem()
{
	auto* col = AddComponent<Collider>();
	col->SetName(L"RollingItem");
	col->SetTrigger(true);
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
	if (isShow)
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
}
void RollingItem::SetDownSpeed(float _speed)
{
	speed = _speed;
}

void RollingItem::SetIsShow(bool _isShow)
{
	isShow = _isShow;
}

void RollingItem::EnterCollision(Collider* _other)
{
	if (_other->IsTrigger())
	{
		cout << "Enter" << endl;
		if (_other->GetName() == L"Rolling")
		{
			SetIsShow(true);
		}
	}
}

void RollingItem::StayCollision(Collider* _other)
{
}

void RollingItem::ExitCollision(Collider* _other)
{
	if (_other->IsTrigger())
	{
		if (_other->GetName() == L"Rolling")
		{
			SetIsShow(false);
		}
	}
}

void RollingItem::SetTexture(wstring _textureName)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(_textureName);
}
