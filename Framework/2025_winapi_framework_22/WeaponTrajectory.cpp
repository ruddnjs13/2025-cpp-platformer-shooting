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

void WeaponTrajectory::DestoryTrajectory()
{
    if (m_TextureObjects.size() < 1)
        m_TextureObjects.resize(1, nullptr);

    if (m_Trajectory != nullptr)
    {
        GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_Trajectory);
        m_Trajectory = nullptr;
    }

    for (int i = 0; i < 1; i++)
    {
        if (m_TextureObjects[i] != nullptr)
        {
            GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_TextureObjects[i]);
            m_TextureObjects[i] = nullptr;
        }
    }
}


void WeaponTrajectory::ShowTrajectory(float _angleValue,Vec2 angle, Vec2 pos, Vec2 size, Object* owner, Weapon* _weapon)
{
    weapon = _weapon;

    StoreAngleValue(_angleValue);

    if (m_TextureObjects.size() < 1)
        m_TextureObjects.resize(1, nullptr);

    if (m_Trajectory != nullptr)
    {
        GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_Trajectory);
        m_Trajectory = nullptr;
    }

    for (int i = 0; i < 1; i++)
    {
        if (m_TextureObjects[i] != nullptr)
        {
            GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_TextureObjects[i]);
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
            for (int i = 0; i < 1; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(80));

                if (m_Trajectory == nullptr)
                    continue;

                TextureObject* textureObject = new TextureObject;

                Vec2 pos = m_Trajectory->GetPos(); 
                Weapon* owner = dynamic_cast<Weapon*>(GetOwner());

                if (owner && owner->GetOwner())
                {
                    textureObject->SetOffset(pos - owner->GetOwner()->GetPos());
                    textureObject->SetOwner(owner->GetOwner());
                    textureObject->SetAngleValue(angleValue);
                }
                else
                {
                    textureObject->SetOffset({ 0, 0 });
                    textureObject->SetOwner(nullptr);
                    textureObject->SetAngleValue(angleValue);
                }

                textureObject->SetSize({ 30, 30 });
                m_TextureObjects[i] = textureObject;

                GET_SINGLE(SceneManager)->GetCurScene()->AddObject(textureObject, Layer::PROJECTILE);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            if (weapon)
                weapon->isRotation = true;
            

        }).detach();
}


