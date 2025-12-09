#include "pch.h"
#include "InGameCanvas.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Image.h"
#include "Slider.h"
#include "MatchScoreUI.h"
#include "GameManager.h"


void InGameCanvas::Init()
{

	p1_HpBar = new Slider();
	p1_HpBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"P1_Boarder"), GET_SINGLE(ResourceManager)->GetTexture(L"HpFill"));
	p1_HpBar->SetPos({ 220, 80 });
	p1_HpBar->SetSize({ 384, 96 });
	p1_HpBar->SetFill({ 265,70 }, { 270,30 });

	p1_SteminaBar = new Slider();
	p1_SteminaBar->isNotBoarder = true;
	p1_SteminaBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"P1_Boarder"), GET_SINGLE(ResourceManager)->GetTexture(L"SteminaFill"));
	p1_SteminaBar->SetFill({ 262,100 }, { 252,6 });


	p2_HpBar = new Slider();
	p2_HpBar->isReverse = true;
	p2_HpBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"P2_Boarder"), GET_SINGLE(ResourceManager)->GetTexture(L"HpFill"));
	p2_HpBar->SetPos({ 1060, 80 });
	p2_HpBar->SetSize({ 384, 96 });
	p2_HpBar->SetFill({ 1015,70 }, { 270,30 });

	p2_SteminaBar = new Slider();
	p2_SteminaBar->isReverse = true;
	p2_SteminaBar->isNotBoarder = true;
	p2_SteminaBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"P2_Boarder"), GET_SINGLE(ResourceManager)->GetTexture(L"SteminaFill"));
	p2_SteminaBar->SetFill({ 1018,100 }, { 252,6 });

	matchScoreUI = new MatchScoreUI();

	matchScoreUI->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Colon"));
	matchScoreUI->InitScoreTexture(
		GET_SINGLE(ResourceManager)->GetTexture(L"Zero_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"One_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Two_Red"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Zero_Blue"),
		GET_SINGLE(ResourceManager)->GetTexture(L"One_Blue"),
		GET_SINGLE(ResourceManager)->GetTexture(L"Two_Blue")
		);
	matchScoreUI->SetPos({ 640,80 });
	matchScoreUI->SetSize({ 100,100 });

	GET_SINGLE(GameManager)->SetMatchScoreUI(matchScoreUI);

	
	AddUIElement(matchScoreUI);
	AddUIElement(p1_HpBar);
	AddUIElement(p2_HpBar);
	AddUIElement(p1_SteminaBar);
	AddUIElement(p2_SteminaBar);
}

void InGameCanvas::Release()
{
	Canvas::Release();
	p1_HpBar = nullptr;
	p2_HpBar = nullptr;
	p1_SteminaBar = nullptr;
	p2_SteminaBar = nullptr;

}

void InGameCanvas::Update()
{
	Canvas::Update();
}
