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
#include "Health.h"
#include "Rigidbody.h"
#include "Weapon.h"
#include "SlotReel.h"
Player::Player()
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\plane.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerIdle");
	Collider* c = AddComponent<Collider>();
	c->SetSize({ 28,28 });
	c->SetName(L"Player");
	auto * r = AddComponent<Rigidbody>();
	auto* health = AddComponent<Health>();
	health->SetHealth(100);
	//GetComponent<Rigidbody>()->SetUseGravity(false);
	SetStamina(100);
	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"PlayerIdle",
		m_pTex, 
		{0.f,0.f},
		{16.f,16.f},
		{16.f,0.f},
		6,0.1f
	);
	//animator->Play(L"PlayerIdle");
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerWalk");
	animator->CreateAnimation
	(
		L"PlayerRun",
		m_pTex,
		{ 0.f,0.f },
		{ 16.f,16.f },
		{ 16.f,0.f },
		6, 0.1f
	);
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDie");
	animator->CreateAnimation
	(
		L"PlayerDie",
		m_pTex,
		{ 0.f,0.f },
		{ 16.f,16.f },
		{ 16.f,0.f },
		4, 0.1f
	);
	animator->Play(L"PlayerDie");

	GET_SINGLE(TurnManager)->RaiseEvent(TurnType::Select, [this]()
		{
			
		});
}

Player::~Player()
{
	// DELETE
}
void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	//RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	// blt 5총사 
	// 1. bitblt - 가장 빠른 대신 무식합니다. 
	//::BitBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, width
	//	, height
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, SRCCOPY);

	////// 2. Transparent - 색깔을 뺄 수 있음
	/*HDC tHDC = m_pTex->GetRotateTextureDC(GetAngle(), 0, 0, width, height);
	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, tHDC
		, 0, 0,width, height,
		RGB(255,0,255));*/

	////// 3. StretchBlt - 확대, 축소, 반전
	//::StretchBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, width, height,SRCCOPY);

	//// 4. 회전
	//::PlgBlt()
	//
	
	//// 5. 
	//::AlphaBlend()
	ComponentRender(_hdc);
}

void Player::StayCollision(Collider* _other)
{
}

void Player::EnterCollision(Collider* _other)
{	
	if (_other->GetName() == L"Floor")
	{
		collCnt++;
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGrounded(true);
		cout << collCnt;
	}
}


void Player::ExitCollision(Collider* _other)
{
	if (_other->GetName() == L"Floor")
	{
		collCnt--;
		std::wcout << _other->GetName();
		cout << collCnt;
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGrounded(collCnt > 0);
	}
}

void Player::ChangeState(PlayerState _newState)
{
	m_prevState = m_state;
	m_state = _newState;
	Animator* animator = GetComponent<Animator>();

	switch (m_state)
	{
	case PlayerState::IDLE:
	{
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerIdle");
		animator->Play(L"PlayerIdle");
	}
	break;
	case PlayerState::RUN:
	{
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerWalk");
		animator->Play(L"PlayerRun");
	}
	break;
	case PlayerState::JUMP:
		break;
	case PlayerState::DIE:
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDie");
		animator->Play(L"PlayerDie", PlayMode::Once);
		break;
	default:
		break;
	}
}

void Player::Update()
{
	Health* health = GetComponent<Health>();
	if (health->IsDead()) return;
	Rigidbody* rb = GetComponent<Rigidbody>();
	//Vec2 pos = GetPos();

	//if (GET_KEY(KEY_TYPE::W))
	//	pos.y -= 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::S))
	//	pos.y += 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::A))
	//	pos.x -= 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::D))
	//	pos.x += 200.f * fDT;
	//SetPos(pos);

	Vec2 dir = {};
	double angle = GetAngle();



	if (CheckPlayerTurn(TurnType::Player1) && GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player1)
	{

		isCanSlotReel = true;
		if (m_stamina > 0)
		{
			if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
			if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;
			//if (GET_KEY(KEY_TYPE::W)) angle += 0.1f;
			//if (GET_KEY(KEY_TYPE::S)) angle -= 0.1f;
			if (GET_KEYDOWN(KEY_TYPE::SPACE))
			{
				rb = GetComponent<Rigidbody>();
				if (rb->IsGrounded())
				{
					m_stamina -= 10;
					Jump();
					//CreateProjectile();
				}
			
			}
		}

		if (GET_KEYDOWN(KEY_TYPE::F))
		{
			GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Player2);
		}
		if (GET_KEY(KEY_TYPE::RSHIFT))
		{
			slotReel->DestroyWeapon();
		}
		
	}
	else if (CheckPlayerTurn(TurnType::Player2) && GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player2)
	{
		isCanSlotReel = true;
		if (m_stamina > 0)
		{
			if (GET_KEY(KEY_TYPE::LEFT)) dir.x -= 1.f;
			if (GET_KEY(KEY_TYPE::RIGHT)) dir.x += 1.f;
			//if (GET_KEY(KEY_TYPE::UP)) angle += 0.1f;
			//if (GET_KEY(KEY_TYPE::DOWN)) angle -= 0.1f;
			if (GET_KEY(KEY_TYPE::RSHIFT))
			{
				rb = GetComponent<Rigidbody>();
				if (rb->IsGrounded())
				{
					m_stamina -= 10;
					Jump();
				}
			}
		}

		if (GET_KEY(KEY_TYPE::RSHIFT))
		{
			slotReel->DestroyWeapon();
		}
	}
	if (m_state != PlayerState::RUN && dir.Length() > 0.f)
	{
		ChangeState(PlayerState::RUN);
	}
	else if (m_state != PlayerState::IDLE && dir.Length() == 0.f)
	{
		ChangeState(PlayerState::IDLE);
	}
	Translate({dir.x * fDT * 200.f, dir.y * fDT * 200.f});
	if (std::abs(dir.x) > 0.f) m_stamina -= 0.1f;
	m_pTex->SetFlipped(dir.x < 0.f);
	//Angle(angle);

	// Q, E 크게 작게 
	//float scaleDelta = 0.f;
	//float scaleSpeed = 1.f;
	//if (GET_KEY(KEY_TYPE::Q))
	//	scaleDelta += scaleSpeed * fDT;
	//if (GET_KEY(KEY_TYPE::E))
	//	scaleDelta -= scaleSpeed * fDT;
	//float factor = scaleSpeed + scaleDelta;
	//Scale({ factor, factor });

	if (GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Select 
		&& GET_SINGLE(TurnManager)->GetCurPlayer() == playerCount && isCanSlotReel == true)
	{
		isCanSlotReel = false;
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
	
	
		int turnNum = m_turnType == TurnType::Player1 ? 1 : 2;
	
		slotReel->SlotRolling(turnNum);
	
		slotReel->SetOwner(this);
	
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(slotReel, Layer::Slot);
	}
}


void Player::CreateProjectile()
{
	Projectile* proj = new Projectile;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	//static float angle = 0.f;
 	//proj->SetAngle(angle * PI / 180.f);
	//angle += 10.f;
	proj->SetDir({0.f, -1.f});
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);
	
}

void Player::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetGrounded(false);
	Vec2 jumpPower{ 0, -50 };
	rb->AddImpulse(jumpPower * 5);
}




