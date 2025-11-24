#pragma once
#include "Bullet.h"
class Texture;

class TestBullet :
    public Bullet
{
public:
    TestBullet();
	~TestBullet();

public:
    void Update() override;
	void Render(HDC _hdc) override;
    void BurstBullet() override;
	void Rotate() override;

private:
	Texture* m_pTex;
};

