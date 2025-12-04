#include "pch.h"
#include "InGameCanvas.h"
#include "ResourceManager.h"

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

	AddUIElement(p1_HpBar);
	AddUIElement(p2_HpBar);


}
