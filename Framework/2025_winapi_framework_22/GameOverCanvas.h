#pragma once
#include "Canvas.h"
#include "MyAction.h"
class Button;
class MatchScoreUI;
class Image;

class GameOverCanvas :
    public Canvas
{
    // Canvas을(를) 통해 상속됨
    void Init() override;
    void Release() override;

private:
    Image* winImage;
    Button* toTitleBtn;
    MyAction<void>::Handle toTitleHandle;
    MatchScoreUI* matchScoreUI;
};

