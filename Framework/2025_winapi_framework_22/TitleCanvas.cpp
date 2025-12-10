#include "pch.h"
#include "TitleCanvas.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void TitleCanvas::Init()
{
    startBtn = new Button();
    guideBtn = new Button();
    exitBtn = new Button();
    gameTitle = new Image();

    {
        Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"StartBtn");
        Texture* texHover = GET_SINGLE(ResourceManager)->GetTexture(L"StartBtn_Hover");
        startBtn->Init(tex, texHover);
        startBtn->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8 * 4 });
        startBtn->SetSize({ 200, 50 });

        startBtnHandle = startBtn->OnClickEvt.AddListener([]() {
            GET_SINGLE(SceneManager)->RequestLoadScene(L"LkwScene");
            });
    }

    {
        Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"GuideBtn");
        Texture* texHover = GET_SINGLE(ResourceManager)->GetTexture(L"GuideBtn_Hover");
        guideBtn->Init(tex, texHover);
        guideBtn->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8 * 5 });
        guideBtn->SetSize({ 200, 50 });
    }

    {
        Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"ExitBtn");
        Texture* texHover = GET_SINGLE(ResourceManager)->GetTexture(L"ExitBtn_Hover");
        exitBtn->Init(tex, texHover);
        exitBtn->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8 * 6 });
        exitBtn->SetSize({ 150, 50 });

        exitBtnHandle = exitBtn->OnClickEvt.AddListener([]() {
            PostQuitMessage(0);
            });
    }


    Texture* titleTex = GET_SINGLE(ResourceManager)->GetTexture(L"GameTitle");

    gameTitle->Init(titleTex);
    gameTitle->SetPos({ WINDOW_WIDTH/2,200 });
    gameTitle->SetSize({400,200});


    AddUIElement(gameTitle);
    AddUIElement(startBtn);
    AddUIElement(guideBtn);
    AddUIElement(exitBtn);
}

void TitleCanvas::Release()
{
    startBtn->OnClickEvt.RemoveListener(startBtnHandle);
    exitBtn->OnClickEvt.RemoveListener(exitBtnHandle);

    Canvas::Release();
    startBtn = nullptr;
    guideBtn = nullptr;
    exitBtn = nullptr;
}
