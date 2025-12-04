#pragma once
#include "Weapon.h"
class Texture;

class TestWeapon2 :
    public Weapon
{
public:
	TestWeapon2();
	~TestWeapon2();

public:
	void Update() override;
	void Rotate();
	void Render(HDC _hdc) override;
	void Shoot();
private:

	Texture* m_pTex;
};

