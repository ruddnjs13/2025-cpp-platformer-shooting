#pragma once
#include "Weapon.h"
#include "Texture.h"

class Rocket :
    public Weapon
{
public:
    Rocket();
    ~Rocket();

public:
	void WeaponFlip();
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();
	void MakeBullet();

private:
	float m_bulletCnt = 0;
	bool m_ismultiShoot = false;
	float m_waitTime = 0;
	Texture* m_pTex;
};

