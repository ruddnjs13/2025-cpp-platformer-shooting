#pragma once
#include "Canvas.h"

class Slider;
class Image;

class InGameCanvas :
    public Canvas
{
    // Canvas을(를) 통해 상속됨
    void Init() override;

    void Update() override;

public:
    Slider* p1_HpBar;
    Slider* p2_HpBar;
    Slider* p1_SteminaBar;
    Slider* p2_SteminaBar;

};

