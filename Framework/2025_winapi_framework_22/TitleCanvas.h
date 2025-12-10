#pragma once
#include "MyAction.h"
#include "Canvas.h"
#include "Button.h"

class Button;


class TitleCanvas :
	public Canvas
{
public:

	// Canvas을(를) 통해 상속됨
	void Init() override;
	void Release() override;

	Button* startBtn;
	MyAction<void>::Handle startBtnHandle;
	Button* guideBtn;
	Button* exitBtn;
	MyAction<void>::Handle exitBtnHandle;

	Image* gameTitle;
};

