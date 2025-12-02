#include "pch.h"
#include "Slider.h"

void Slider::Init(Texture* boarderTexture, Texture* fillTexture, Texture* handleTexture)
{


	boarder = boarderTexture;
	fillBar = fillTexture;
	handle = handleTexture;
}

void Slider::Update()
{
}

void Slider::Render(HDC _hdc)
{
	Vec2 curPos = GetPos();
	Vec2 curSize = GetSize();

	DrawTexture(_hdc, curPos, curSize, boarder);
}

void Slider::SetValue(float amount)
{
}
