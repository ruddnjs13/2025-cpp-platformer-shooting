#pragma once
#include "Weapon.h"

class Texture;

class TestWeapon
	:public Weapon
{
public:
	TestWeapon();
	~TestWeapon();

public:
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();

private:
	Texture* m_pTex;
};

