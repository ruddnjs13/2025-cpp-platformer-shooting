#pragma once
#include "Weapon.h"

class Texture;

class PizzeGun :
    public Weapon
{

public:
	PizzeGun();
	~PizzeGun();

public:
	void WeaponFlip();
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();


private:
	Texture* m_pTex;
};

