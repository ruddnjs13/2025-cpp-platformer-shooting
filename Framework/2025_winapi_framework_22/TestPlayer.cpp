#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "WeaponHolderComponent.h"
#include "TestPlayer.h"
#include "TestWeapon2.h"
#include "TestWeapon.h"
#include "TurnManager.h"

TestPlayer::TestPlayer()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	AddComponent<Collider>();


	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"JiwooFront",
		m_pTex,
		{ 0.f,150.f },
		{ 50.f,50.f },
		{ 50.f,0.f },
		5, 0.1f
	);
	animator->Play(L"JiwooFront");

	m_pWeaponHolder = AddComponent<WeaponHolderComponent>();

	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	pos.x += 10.f;

	Vec2 angle = Vec2(0.f, 0.f);

	m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
		{ pos },
		{ 20.f,20.f });


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::ENEMY);
	weaponCount = 0;

}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Update()
{
	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;
	if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;
	Translate({ dir.x * fDT * 200.f, dir.y * fDT * 200.f });

	// Q, E 크게 작게 
	float scaleDelta = 0.f;
	float scaleSpeed = 1.f;
	if (GET_KEY(KEY_TYPE::Q))
		scaleDelta += scaleSpeed * fDT;
	if (GET_KEY(KEY_TYPE::E))
		scaleDelta -= scaleSpeed * fDT;
	float factor = scaleSpeed + scaleDelta;
	Scale({ factor, factor });

	
	if(GET_KEYDOWN(KEY_TYPE::L))
	{
		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;
		pos.x += 10.f;
		Vec2 angle = Vec2(0.f, 0.f);
		
		m_pWeaponHolder->ChangeWeapon(new TestWeapon2(),
			{ pos },
			{ 20.f,20.f });


		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
	}

	if (GET_KEYDOWN(KEY_TYPE::K))
	{
		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;
		pos.x += 10.f;
		Vec2 angle = Vec2(0.f, 0.f);

		m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
			{ pos },
			{ 20.f,20.f });


		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
	}
}

void TestPlayer::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void TestPlayer::EnterCollision(Collider* _other)
{
}

void TestPlayer::StayCollision(Collider* _other)
{
}

void TestPlayer::ExitCollision(Collider* _other)
{
}
