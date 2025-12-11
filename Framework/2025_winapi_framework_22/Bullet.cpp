#include "pch.h"
#include "Health.h"
#include "SceneManager.h"
#include "Collider.h"
#include "TurnManager.h"
#include "Bullet.h"
#include <thread>

Bullet::Bullet() 
	: m_angle(0.f)
	, m_dir(1.f, 1.f)
	, m_damage(0.f)
	, m_speed(0.f)
{
	std::thread([this]() {
		std::this_thread::sleep_for(std::chrono::seconds(6));
		GET_SINGLE(SceneManager)->RequestDestroy(this);
		}).detach();
}

Bullet::~Bullet()
{
}

void Bullet::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		_other->GetOwner()->GetComponent<Health>()->TakeDamage(100);
		BurstBullet();
		DestoyThis();
	}

	if (_other->GetName() == L"Floor")
	{
		BurstBullet();
		DestoyThis();
		DestroyOther(_other);
	}
}

void Bullet::StayCollision(Collider* _other)
{

}

void Bullet::ExitCollision(Collider* _other)
{

}
