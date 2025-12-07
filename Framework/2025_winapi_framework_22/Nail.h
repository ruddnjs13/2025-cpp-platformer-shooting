#pragma once
#include "Bullet.h"

class Texture;
class Nail :
    public Bullet
{
public:
    Nail();
    ~Nail();

public:
    void Update() override;
    void Render(HDC _hdc) override;
    void BurstBullet() override;
    void Rotate() override;
private:
    Texture* m_pTex;
};

