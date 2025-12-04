#include "pch.h"
#include "TitleCanvas.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void TitleCanvas::Init()
{
	startBtn = new Button();
	guideBtn = new Button();
	exitBtn = new Button();

	Texture* startTexture = GET_SINGLE(ResourceManager)->GetTexture(L"StartBtn");
	Texture* startHoverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"StartBtn_Hover");
	startBtn->Init(startTexture, startHoverTexture);

	startBtn->SetPos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 8 * 5 });
	startBtn->SetSize({200,50});

	startBtn->OnClickEvt.AddListener(std::bind(&TitleCanvas::GotoInGame,this));

	Texture* guideTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GuideBtn");
	Texture* guideHoverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GuideBtn_Hover");
	guideBtn->Init(guideTexture, guideHoverTexture);

	guideBtn->SetPos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 8 * 6 });
	guideBtn->SetSize({ 200,50 });

	guideBtn->OnClickEvt.AddListener(std::bind(&TitleCanvas::GotoInGame, this));

	Texture* exitTexture = GET_SINGLE(ResourceManager)->GetTexture(L"ExitBtn");
	Texture* exitHoverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"ExitBtn_Hover");
	exitBtn->Init(exitTexture, exitHoverTexture);

	exitBtn->SetPos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 8*7 });
	exitBtn->SetSize({ 200,50 });

	exitBtn->OnClickEvt.AddListener(std::bind(&TitleCanvas::GotoInGame, this));

	backgroundPanel = new Image();
	Texture* backgroundTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Background");
	backgroundPanel->Init(backgroundTexture);

	backgroundPanel->SetPos({WINDOW_WIDTH/2,WINDOW_HEIGHT/2});
	backgroundPanel->SetSize({WINDOW_WIDTH,WINDOW_HEIGHT});

	AddUIElement(backgroundPanel);

	AddUIElement(startBtn);
	AddUIElement(guideBtn);
	AddUIElement(exitBtn);


}

void TitleCanvas::GotoInGame()
{
	GET_SINGLE(SceneManager)->LoadScene(L"LkwScene");
}
