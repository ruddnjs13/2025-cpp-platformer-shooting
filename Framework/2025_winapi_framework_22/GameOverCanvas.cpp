#include "pch.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "GameOverCanvas.h"
#include "SceneManager.h"
#include "MatchScoreUI.h"
#include "Button.h"

void GameOverCanvas::Init()
{
	matchScoreUI = new MatchScoreUI();

	matchScoreUI->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Colon"));

	matchScoreUI->InitScoreTexture(
		GET_SINGLE(ResourceManager)->GetTexture(L"Zero_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"One_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Two_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Three_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Zero_Blue"),
		GET_SINGLE(ResourceManager)->GetTexture(L"One_Blue"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Two_Blue"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Three_Blue")
	);
	matchScoreUI->SetPos({ 640,80 });
	matchScoreUI->SetSize({ 100,100 });

	matchScoreUI->SetScore(GET_SINGLE(GameManager)->GetPlayer1Score()
		, GET_SINGLE(GameManager)->GetPlayer2Score());

	toTitleBtn = new Button();

	toTitleBtn->Init(GET_SINGLE(ResourceManager)->GetTexture(L"TitleBtn"),
		GET_SINGLE(ResourceManager)->GetTexture(L"TitleBtn_Hover"));

	toTitleBtn->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8 * 6 });
	toTitleBtn->SetSize({ 150, 50 });
	toTitleHandle = toTitleBtn->OnClickEvt.AddListener([]() {
		GET_SINGLE(SceneManager)->RequestLoadScene(L"TitleScene");
		GET_SINGLE(GameManager)->ResetGame();
		});


	winImage = new Image();
	if (GET_SINGLE(GameManager)->GetPlayer1Score()
		> GET_SINGLE(GameManager)->GetPlayer2Score())
	{
		winImage->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Player1_Win"));
	}
	else
	{
		winImage->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Player2_Win"));
	}

	winImage->SetPos({WINDOW_WIDTH/2, 500});
	winImage->SetSize({ 400,100 });

	AddUIElement(toTitleBtn);
	AddUIElement(matchScoreUI);
}

void GameOverCanvas::Release()
{
	toTitleBtn->OnClickEvt.RemoveListener(toTitleHandle);
	Canvas::Release();
}
