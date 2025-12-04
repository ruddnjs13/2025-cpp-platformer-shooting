#pragma once
#include "Canvas.h"
#include "Image.h"
class InGameCanvas :
    public Canvas
{
    // Canvas을(를) 통해 상속됨
    void Init() override;

private:
    Image* background;
};

