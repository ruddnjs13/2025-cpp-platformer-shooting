#pragma once
#include "Canvas.h"

class MatchScoreUI;

class GameOverCanvas :
    public Canvas
{
    // Canvas을(를) 통해 상속됨
    void Init() override;

private:
    MatchScoreUI* matchScoreUI;
};

