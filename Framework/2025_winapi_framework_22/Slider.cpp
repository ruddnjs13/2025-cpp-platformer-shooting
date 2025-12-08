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

    if(!isNotBoarder)
        DrawTexture(_hdc, curPos, curSize, boarder);
    if(isReverse)
        DrawTextureClipped(_hdc, fillPos, fillSize, fillBar, ratio,true);
    else
        DrawTextureClipped(_hdc, fillPos, fillSize, fillBar, ratio);
}

void Slider::SetValue(float value)
{
    currentValue = (float)std::clamp(value, minValue, maxValue);

}

void Slider::SetFill(Vec2 pos, Vec2 size)
{
    fillPos = pos;
    fillSize = size;
}
