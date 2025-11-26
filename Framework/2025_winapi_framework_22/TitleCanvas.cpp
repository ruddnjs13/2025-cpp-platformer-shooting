#include "pch.h"
#include "TitleCanvas.h"
#include "ResourceManager.h"

void TitleCanvas::Init()
{
	startBtn = Button();

	Texture* defaultTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
	Texture* hoverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
	startBtn.Init(defaultTexture, hoverTexture);

	startBtn.SetPos({ 400,400 });
	startBtn.SetSize({400,100});

	AddUIElement(&startBtn);
}
