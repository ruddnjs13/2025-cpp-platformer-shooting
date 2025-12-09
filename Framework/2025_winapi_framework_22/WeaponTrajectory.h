#pragma once
#include "Component.h"

class Trajectory;
class TextureObject;
class Weapon;

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
	void SetTrajectoryDir(Vec2 angle);
	void SetTrajectoryPos(Vec2 pos);
	void SetTrajectorySize(Vec2 size);
	void StoreAngleValue(float _angleValue) { angleValue = _angleValue; }
	void DestoryTrajectory();
public:
	void ShowTrajectory(float _angleValue, Vec2 angle, Vec2 pos, Vec2 size, Object* owner, Weapon* _weapon, bool isFlip);
	
public:
	float angleValue = 0;
	bool isShoot = true;
private:
	Weapon* weapon;
	std::vector<TextureObject*> m_TextureObjects;
	Trajectory* m_Trajectory = nullptr;
};

