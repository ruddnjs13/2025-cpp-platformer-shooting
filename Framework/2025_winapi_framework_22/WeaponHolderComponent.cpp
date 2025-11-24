#include "pch.h"
#include "WeaponHolderComponent.h"
#include "Weapon.h"
#include "SceneManager.h"

WeaponHolderComponent::WeaponHolderComponent()
{
	
}

WeaponHolderComponent::~WeaponHolderComponent()
{

}

void WeaponHolderComponent::Init()
{
}

void WeaponHolderComponent::LateUpdate()
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();
	pos.x += 20.f;

	m_pCurrentWeapon->SetPos(pos + m_pCurrentWeapon->GetOffSetPos());
}

void WeaponHolderComponent::Render(HDC hDC)
{
}

void WeaponHolderComponent::ChangeWeapon(Weapon* weapon, Vec2 pos, Vec2 size)
{
	if (m_pCurrentWeapon != nullptr)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(m_pCurrentWeapon);
		m_pCurrentWeapon = nullptr;
	}

	m_pCurrentWeapon = weapon;
	m_pCurrentWeapon->SetOwner(GetOwner());

	SetWeaponPos(pos);
	SetWeaponSize(size);
}


void WeaponHolderComponent::SetWeaponPos(Vec2 pos)
{
	if (m_pCurrentWeapon == nullptr || GetOwner() == nullptr)
		return;

	m_pCurrentWeapon->SetPos(pos);
}

void WeaponHolderComponent::SetWeaponSize(Vec2 size)
{
	if (m_pCurrentWeapon == nullptr)
		return;

	
	m_pCurrentWeapon->SetSize(size);
}
