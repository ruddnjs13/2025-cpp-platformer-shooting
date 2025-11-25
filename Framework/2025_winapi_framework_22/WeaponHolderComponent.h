#pragma once

#include "Component.h"

class Weapon;

class WeaponHolderComponent
	: public Component
{
public:
	WeaponHolderComponent();
	~WeaponHolderComponent();
public:
	void Init() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;

public:
	void ChangeWeapon(Weapon* weapon, Vec2 pos, Vec2 size, float angle);
	Weapon* GetCurrentWeapon() const { return m_pCurrentWeapon; }

private:
	void SetWeaponRotation(float angle);
	void SetWeaponPos(Vec2 pos);
	void SetWeaponSize(Vec2 size);

private:
	Weapon* m_pCurrentWeapon = nullptr;
};

