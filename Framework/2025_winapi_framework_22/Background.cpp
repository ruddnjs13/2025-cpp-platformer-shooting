#include "pch.h"
#include "Background.h"
#include "Texture.h"

void Background::Init(Texture * texture)
{
	m_Texture = texture;
}

void Background::Update()
{
}

void Background::Render(HDC _hdc)
{
	Vec2 curSize = GetSize();
	Vec2 curPos = GetPos();

	HDC memDC = m_Texture->GetTextureDC();

	BitBlt(
		_hdc,
		curPos.x - curSize.x / 2,
		curPos.y - curSize.y / 2,
		curSize.x,
		curSize.y,
		memDC,
		0, 0,
		SRCCOPY
	);
}
