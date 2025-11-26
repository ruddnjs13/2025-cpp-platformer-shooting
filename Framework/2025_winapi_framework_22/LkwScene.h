#pragma once
#include "Scene.h"
#include "Button.h"


class LkwScene :
    public Scene
{

private : 
    Button* testBtn = nullptr;
    Image* testImage = nullptr;

    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update() override;
};

