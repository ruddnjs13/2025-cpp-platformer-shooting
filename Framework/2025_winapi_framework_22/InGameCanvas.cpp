#include "pch.h"
#include "InGameCanvas.h"
#include "ResourceManager.h"
#include "InputManager.h"


void InGameCanvas::Init()
{
	p1_HpBar = new Slider();
	p1_HpBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Boarder")
		, GET_SINGLE(ResourceManager)->GetTexture(L"Fill_Red"));
	p1_HpBar->SetPos({ 280, 50 });
	p1_HpBar->SetSize({ 400, 80 });

	p2_HpBar = new Slider();
	p2_HpBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Boarder")
		, GET_SINGLE(ResourceManager)->GetTexture(L"Fill_Blue"));
	p2_HpBar->SetPos({ 1000, 50 });
	p2_HpBar->SetSize({ 400, 80 });

	p1_SteminaBar = new Slider();
	p1_SteminaBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Boarder")
		, GET_SINGLE(ResourceManager)->GetTexture(L"Fill_Yellow"));
	p1_SteminaBar->SetPos({ 180, 90 });
	p1_SteminaBar->SetSize({ 200, 40 });

	p2_SteminaBar = new Slider();
	p2_SteminaBar->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Boarder")
		, GET_SINGLE(ResourceManager)->GetTexture(L"Fill_Yellow"));
	p2_SteminaBar->SetPos({ 1100, 90 });
	p2_SteminaBar->SetSize({ 200, 40 });

	AddUIElement(p1_HpBar);
	AddUIElement(p2_HpBar);
	AddUIElement(p1_SteminaBar);
	AddUIElement(p2_SteminaBar);


}

void InGameCanvas::Update()
{
	Canvas::Update();
	if (GET_KEYDOWN(KEY_TYPE::U))
		p2_SteminaBar->SetValue(50);
}
