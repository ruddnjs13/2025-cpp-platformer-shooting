#include "pch.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "GameOverCanvas.h"
#include "MatchScoreUI.h"

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

	AddUIElement(matchScoreUI);
}
