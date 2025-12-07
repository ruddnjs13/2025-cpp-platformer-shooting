#pragma once
#include "UIElement.h"
#include "Image.h"

class Texture;

class Slider :
    public Image
{
public:
    void Init(Texture* boarderText, Texture* fillTexture);
    // UIElement을(를) 통해 상속됨
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetValue(float value);

public:
    float maxValue = 100;
    float minValue = 0;
    float currentValue = 0;
public:
    Texture* boarder;
    Texture* fillBar;
};

