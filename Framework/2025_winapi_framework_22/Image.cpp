#include "pch.h"
#include "Image.h"

void Image::Init(Texture* texture)
{
	m_texture = texture;
}

void Image::Update()
{
}

void Image::Render(HDC _hdc)
{
	if (m_texture == nullptr) return;

	Vec2 curPos = GetPos();

	Vec2 curSize = GetSize();

	DrawTexture(_hdc, curPos, curSize, m_texture);
}
