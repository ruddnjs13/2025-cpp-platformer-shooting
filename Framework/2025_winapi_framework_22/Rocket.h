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


private:
	Texture* m_pTex;
};

