#include "pch.h"
#include "Bomb.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "TurnManager.h"
#include "SceneManager.h"
#include "Health.h"
#include "Texture.h"
#include <thread>

Bomb::Bomb()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Explosion");

	auto* col = AddComponent<Collider>();
	col->SetName(L"Bomb");
	col->SetTrigger(true);
	col->SetSize({50.f, 50.f});
	FadeOut();

}

Bomb::~Bomb()
{
	
}

void Bomb::Update()
{
}

void Bomb::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height,
		RGB(255, 0, 255));

}

void Bomb::EnterCollision(Collider* _other)
{

	if (_other->GetName() == L"Player")
	{
		_other->GetOwner()->GetComponent<Health>()->TakeDamage(1006);
	}	

	if(_other->GetName() == L"Floor")
	{
		GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
	}
}

void Bomb::StayCollision(Collider* _other)
{
}

void Bomb::ExitCollision(Collider* _other)
{
}

void Bomb::FadeOut()
{
	std::thread([this]() {	
		std::this_thread::sleep_for(std::chrono::seconds(1));
		GET_SINGLE(SceneManager)->RequestDestroy(this);
		}).detach();
}
