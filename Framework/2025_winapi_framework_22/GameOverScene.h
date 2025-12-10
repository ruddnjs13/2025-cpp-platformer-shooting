#pragma once
#include "Scene.h"

class Player;

class GameOverScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    void Init() override;

    void Render(HDC _hdc) override;

private:
    Player* pPlayer2    ;
    Player* pPlayer1;

};

