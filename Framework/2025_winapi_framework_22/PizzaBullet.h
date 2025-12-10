#pragma once
#include "Bullet.h"

class Texture;

class PizzaBullet :
    public Bullet
{
public:
    PizzaBullet();
    ~PizzaBullet();

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

