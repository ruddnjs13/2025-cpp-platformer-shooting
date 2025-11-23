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
	void Rotate() override;
	void Render(HDC _hdc) override;
	void Shoot() override;

private:
	Texture* m_pTex;
};

