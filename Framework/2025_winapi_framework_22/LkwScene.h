#pragma once
#include "MyAction.h"
#include "Scene.h"

class Player;

class LkwScene :
    public Scene
{
private : 
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update() override;
    void Release() override;

public:
    
    Player* pPlayer2;
    Player* pPlayer1;

    MyAction<int>::Handle p1HealthHandle;
    MyAction<int>::Handle p2HealthHandle;
    MyAction<float>::Handle p1SteminaHandle;
    MyAction<float>::Handle p2SteminaHandle;

    MyAction<int>::Handle p1DeadHandle;
    MyAction<int>::Handle p2DeadHandle;


};

