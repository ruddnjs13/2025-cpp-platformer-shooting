#include "pch.h"
#include "WeaponTrajectory.h"
#include "Trajectory.h"
#include "SceneManager.h"
#include <thread>

WeaponTrajectory::WeaponTrajectory()
{
}

WeaponTrajectory::~WeaponTrajectory()
{
}

void WeaponTrajectory::Init()
{
}

void WeaponTrajectory::LateUpdate()
{
	
}

void WeaponTrajectory::Render(HDC hDC)
{
}

void WeaponTrajectory::SetTrajectoryDir(Vec2 angle)
{
	if (m_Trajectory == nullptr)
		return;
	m_Trajectory->SetDir(angle);
}

void WeaponTrajectory::SetTrajectoryPos(Vec2 pos)
{
	if (m_Trajectory == nullptr)
		return;
	m_Trajectory->SetPos(pos);
}

void WeaponTrajectory::SetTrajectorySize(Vec2 size)
{
	if (m_Trajectory == nullptr)
		return;
	m_Trajectory->SetSize(size);
}




void WeaponTrajectory::ShowTrajectory(Vec2 angle, Vec2 pos, Vec2 size, Object* owner)
{
	if (m_Trajectory != nullptr)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(m_Trajectory);
		m_Trajectory = nullptr;
	}

	Trajectory* trajectory = new Trajectory();

	m_Trajectory = trajectory;

	SetTrajectoryDir(angle);
	SetTrajectoryPos(pos);
	SetTrajectorySize(size);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_Trajectory, Layer::PROJECTILE);
	m_Trajectory->ShowAngle(owner);

}
