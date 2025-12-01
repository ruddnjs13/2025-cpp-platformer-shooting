#pragma once
#include "Canvas.h"
#include "Button.h"

class Button;

class TitleCanvas :
	public Canvas
{
	// Canvas을(를) 통해 상속됨
	void Init() override;

	void GotoTitle();

	Button* startBtn;
	Button* guideBtn;
	Button* exitBtn;
	Image* backgroundPanel;
};

