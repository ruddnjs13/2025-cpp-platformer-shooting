#pragma once
#include "Weapon.h"
class Texture;

class Sniper :
    public Weapon
{
public:
	Sniper();
	~Sniper();

public:
	void WeaponFlip();
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();


private:
	Texture* m_pTex;
};

