#pragma once
#include "Component.h"

class Trajectory;
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

public:
	void ShowTrajectory(Vec2 angle, Vec2 pos, Vec2 size, Object* owner);
	
private:
	
	Trajectory* m_Trajectory = nullptr;
};

