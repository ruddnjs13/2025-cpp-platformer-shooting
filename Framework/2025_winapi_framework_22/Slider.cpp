#include "pch.h"
#include "Slider.h"

void Slider::Init(Texture* boarderTexture, Texture* fillTexture)
{
	boarder = boarderTexture;
	fillBar = fillTexture;

	currentValue = maxValue;
}

void Slider::Update()
{
}

void Slider::Render(HDC _hdc)
{
    Vec2 curPos = GetPos();
    Vec2 curSize = GetSize();

    float ratio = (currentValue / maxValue);

    DrawTexture(_hdc, curPos, curSize, boarder);
    DrawTextureClipped(_hdc, curPos, curSize, fillBar, ratio);
}

void Slider::SetValue(float value)
{
    currentValue = std::clamp(value, minValue, maxValue);

}