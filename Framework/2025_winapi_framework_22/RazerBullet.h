#pragma once
#include "Bullet.h"
class Texture;

class RazerBullet :
    public Bullet
{
public:
    RazerBullet();
    ~RazerBullet();

public:
    void Update() override;
    void Render(HDC _hdc) override;
    void BurstBullet() override;
    void Rotate() override;

    void DestoyThis() override;
    void DestroyOther(Collider* _other) override;
private:
    Texture* m_pTex;
};

