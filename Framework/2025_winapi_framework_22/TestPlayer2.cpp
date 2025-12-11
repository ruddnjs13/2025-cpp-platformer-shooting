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
#include "TestPlayer2.h"

TestPlayer2::TestPlayer2()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	AddComponent<Collider>();


	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"JiwooFront2",
		m_pTex,
		{ 0.f,150.f },
		{ 50.f,50.f },
		{ 50.f,0.f },
		5, 0.1f
	);
	animator->Play(L"JiwooFront2");

	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	pos.x += 10.f;

	Vec2 angle = Vec2(0.f, 0.f);
}

TestPlayer2::~TestPlayer2()
{
}

void TestPlayer2::Update()
{
	Vec2 dir = {};

	if (GET_KEY(KEY_TYPE::LEFT)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::RIGHT)) dir.x += 1.f;
	Translate({ dir.x * fDT * 200.f, dir.y * fDT * 200.f });

	// Q, E 크게 작게 
	//float scaleDelta = 0.f;
	//float scaleSpeed = 1.f;
	//if (GET_KEY(KEY_TYPE::Q))
	//	scaleDelta += scaleSpeed * fDT;
	//if (GET_KEY(KEY_TYPE::E))
	//	scaleDelta -= scaleSpeed * fDT;
	//float factor = scaleSpeed + scaleDelta;
	//Scale({ factor, factor });



	if (GET_KEYDOWN(KEY_TYPE::L))
	{
		if (slotReel != nullptr)
		{
			GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(slotReel);
			slotReel = nullptr;
		}

		slotReel = new SlotReel();
		slotReel->SetSize({ 60, 60 });

		Vec2 pos = GetPos();

		pos.y -= 60;

		slotReel->SetPos(pos);


		slotReel->SlotRolling(2);


		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(slotReel, Layer::Slot);
	}
}

void TestPlayer2::Render(HDC _hdc)
{
}

void TestPlayer2::EnterCollision(Collider* _other)
{
}

void TestPlayer2::StayCollision(Collider* _other)
{
}

void TestPlayer2::ExitCollision(Collider* _other)
{
}
