#pragma once
#include "Component.h"
class WeaponTrajectory :
    public Component
{
public:
	WeaponTrajectory();
	~WeaponTrajectory();
public:
	void Init() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;

public:
	void ShowTrajectory();
};

