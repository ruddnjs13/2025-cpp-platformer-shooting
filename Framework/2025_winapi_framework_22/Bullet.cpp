#include "pch.h"
#include "Health.h"
#include "SceneManager.h"
#include "Collider.h"
#include "TurnManager.h"
#include "Bullet.h"

Bullet::Bullet() 
	: m_angle(0.f)
	, m_dir(1.f, 1.f)
	, m_damage(0.f)
	, m_speed(0.f)
{
}

Bullet::~Bullet()
{
	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
}

void Bullet::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		_other->GetOwner()->GetComponent<Health>()->TakeDamage(100);
		BurstBullet();
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}

	if (_other->GetName() == L"Floor")
	{
		BurstBullet();
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}

void Bullet::StayCollision(Collider* _other)
{

}

void Bullet::ExitCollision(Collider* _other)
{

}
