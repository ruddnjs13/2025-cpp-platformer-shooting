#pragma once
#include "Scene.h"


class LkwScene :
    public Scene
{
private : 
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update() override;
};

