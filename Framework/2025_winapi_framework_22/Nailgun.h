#pragma once
#include "Weapon.h"

class Texture;

class Nailgun :
    public Weapon
{
public:
	Nailgun();
	~Nailgun();

public:
	void WeaponFlip();
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();


private:
	Texture* m_pTex;
};

