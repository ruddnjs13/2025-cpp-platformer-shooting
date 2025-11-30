#include "pch.h"
#include "TitleCanvas.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void TitleCanvas::Init()
{
	startBtn = new Button();

	Texture* defaultTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
	Texture* selectTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
	startBtn->Init(defaultTexture, selectTexture);

	startBtn->SetPos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 });
	startBtn->SetSize({100,25});

	startBtn->OnClickEvt.AddListener(std::bind(&TitleCanvas::GotoTitle,this));

	AddUIElement(startBtn);
}

void TitleCanvas::GotoTitle()
{
	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
