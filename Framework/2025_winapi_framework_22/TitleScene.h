#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
public:
    ~TitleScene();
public:
    // Scene을(를) 통해 상속됨
    void Init() override;

public:
};

