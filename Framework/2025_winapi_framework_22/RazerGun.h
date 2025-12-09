#pragma once
#include "Weapon.h"

class Texture;

class RazerGun :
    public Weapon
{
public:
	RazerGun();
	~RazerGun();

public:
	void WeaponFlip();
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();

private:
	Texture* m_pTex;
};

