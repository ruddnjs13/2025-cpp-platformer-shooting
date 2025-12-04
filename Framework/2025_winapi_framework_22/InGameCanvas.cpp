#include "pch.h"
#include "InGameCanvas.h"
#include "ResourceManager.h"

void InGameCanvas::Init()
{
	background = new Image();

	background->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	background->SetSize({WINDOW_WIDTH,WINDOW_HEIGHT});
	background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Backround"));

	AddUIElement(background);
}
