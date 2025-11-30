#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TextureObject.h"

TextureObject::TextureObject()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AimLine");
}

TextureObject::~TextureObject()	
{
}

void TextureObject::Update()
{
}

void TextureObject::Render(HDC _hdc)
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

void TextureObject::LateUpdate()
{
	Object* owner = GetOwner();

	if (owner != nullptr)
	{
		Vec2 pos = owner->GetPos();

		SetPos(pos + GetOffset());
	}
}
