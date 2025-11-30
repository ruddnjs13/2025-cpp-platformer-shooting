#include "pch.h"
#include "WeaponTrajectory.h"
#include "Trajectory.h"
#include "Weapon.h"
#include "SceneManager.h"
#include "TextureObject.h"
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
    if (m_TextureObjects.size() < 6)
        m_TextureObjects.resize(6, nullptr);

    if (m_Trajectory != nullptr)
    {
        GET_SINGLE(SceneManager)->RequestDestroy(m_Trajectory);
        m_Trajectory = nullptr;
    }


    for (int i = 0; i < 6; i++)
    {
        if (m_TextureObjects[i] != nullptr)
        {
            GET_SINGLE(SceneManager)->RequestDestroy(m_TextureObjects[i]);
            m_TextureObjects[i] = nullptr;
        }
    }

    Trajectory* trajectory = new Trajectory();
    m_Trajectory = trajectory;

    SetTrajectoryDir(angle);
    SetTrajectoryPos(pos);
    SetTrajectorySize(size);

    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_Trajectory, Layer::PROJECTILE);


    std::thread([this]()
        {
            for (int i = 0; i < 6; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                cout << GetOwner()->GetPos().x << endl;
                TextureObject* textureObject = new TextureObject;
                Vec2 pos = m_Trajectory->GetPos();
                Weapon* owner = dynamic_cast<Weapon*>(GetOwner());
                textureObject->SetOffset(pos - owner->GetOwner()->GetPos());
                textureObject->SetOwner(owner->GetOwner());
                textureObject->SetSize({ 20, 20 });
                m_TextureObjects[i] = textureObject;
                GET_SINGLE(SceneManager)->GetCurScene()->AddObject(textureObject, Layer::PROJECTILE);
            }
        }).detach();
}

