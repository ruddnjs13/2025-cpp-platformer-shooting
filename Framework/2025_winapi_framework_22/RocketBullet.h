#pragma once
#include "Bullet.h"
class RocketBullet :
    public Bullet
{
public:
    RocketBullet();
    ~RocketBullet();

public:
    void BulletFlip();
    void Update() override;
    void Render(HDC _hdc) override;
    void BurstBullet() override;
    void Rotate() override;
    void DestoyThis() override;
    void DestroyOther(Collider* _other) override;

private:
    Texture* m_pTex;

};

