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
	Collider* c = AddComponent<Collider>();
	GET_SINGLE(ResourceManager)->GetTexture(L"Player1");
	c->SetSize({ 28,28 });
	c->SetName(L"Player");
	SetIsFigures(false);
	auto * r = AddComponent<Rigidbody>();
	auto* health = AddComponent<Health>();
	health->SetHealth(100);
	r->SetFriction(0);
	SetStamina(100);
	AddComponent<Animator>();

	GET_SINGLE(TurnManager)->RaiseEvent(TurnType::Select, [this]()
		{
			
		});
}

void Player::SetPlayerType()
{
	auto* animator = GetComponent<Animator>();
	if (m_turnType == TurnType::Player1)
	{
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Idle");
		animator->CreateAnimation
		(L"Player1Idle",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			6, 0.1f
		);
		animator->Play(L"Player1Idle");
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Walk");
		animator->CreateAnimation
		(
			L"Player1Walk",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			6, 0.1f
		);
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Die");
		animator->CreateAnimation
		(
			L"Player1Die",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			4, 0.3f
		);
	}
	else if (m_turnType == TurnType::Player2)
	{
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Idle");
		animator->CreateAnimation
		(L"Player2Idle",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			6, 0.1f
		);
		animator->Play(L"Player2Idle");
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Walk");
		animator->CreateAnimation
		(
			L"Player2Walk",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			6, 0.1f
		);
		m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Die");
		animator->CreateAnimation
		(
			L"Player2Die",
			m_pTex,
			{ 0.f,0.f },
			{ 16.f,16.f },
			{ 16.f,0.f },
			4, 0.3f
		);
	}
}

Player::~Player()
{
	// DELETE
}
void Player::Render(HDC _hdc)
{
	m_pTex->SetFlipped(m_isFlipped);
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
	if (_other->GetName() == L"DieZone")
	{
		auto* health = GetComponent<Health>();
		health->TakeDamage(-INT_MAX);
	}
}

void Player::ExitCollision(Collider* _other)
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	if (_other->GetName() == L"Floor")
	{
	}
	rb->SetGrounded(false);
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
		if (m_turnType == TurnType::Player1)
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Idle");
			animator->Play(L"Player1Idle");
		}
		else
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Idle");
			animator->Play(L"Player2Idle");
		}
	}
	break;
	case PlayerState::RUN:
	{
		if (m_turnType == TurnType::Player1)
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Walk");
			animator->Play(L"Player1Walk");
		}
		else
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Walk");
			animator->Play(L"Player2Walk");
		}
	}
	break;
	case PlayerState::JUMP:
		break;
	case PlayerState::DIE:
		PLAY_SOUND(L"PlayerDeadSFX");
		if (m_turnType == TurnType::Player1)
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player1Die");
			animator->Play(L"Player1Die", PlayMode::Once);
		}
		else
		{
			m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player2Die");
			animator->Play(L"Player2Die", PlayMode::Once);
		}
		if (GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player1 || GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player2)
		{
			slotReel->DestroyWeapon();			
		}
		onDeadEvent.Invoke(playerCount);
		break;
	default:
		break;
	}
}

void Player::Update()
{
	if (IsFigures())
	{
		if (m_state != PlayerState::IDLE)
		{
			m_state = PlayerState::IDLE;
			ChangeState(PlayerState::IDLE);
		}
		return;
	}
	Health* health = GetComponent<Health>();
	Rigidbody* rb = GetComponent<Rigidbody>();
	if (health->IsDead() && m_state != PlayerState::DIE)
	{
		rb->SetVelocity({ 0.f, 0.f });
		ChangeState(PlayerState::DIE);
		return;
	}
	if (health->IsDead()) return;
	if (m_isShooting && GET_SINGLE(TurnManager)->GetCurrentTurn() != m_turnType)
		m_isShooting = false;

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

	Vec2 dir = {0.f, 0.f};

	if (!m_isShooting)
	{
		if (CheckPlayerTurn(TurnType::Player1) && GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player1)
		{

			if (GET_KEYDOWN(KEY_TYPE::F) && m_isDestroy)
			{
				m_isDestroy = false;
				m_isShooting = true;
				SetStamina(m_maxStamina);
				slotReel->DestroyWeapon();
			}

			isCanSlotReel = true;
			if (m_stamina > 0)
			{
				if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
				if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;


				if (GET_KEYDOWN(KEY_TYPE::SPACE))
				{
					rb = GetComponent<Rigidbody>();
					if (rb->IsGrounded())
					{
						AddStamina(-15);
						Jump();
					}

				}
			}


		}
		else if (CheckPlayerTurn(TurnType::Player2) && GET_SINGLE(TurnManager)->GetCurrentTurn() == TurnType::Player2)
		{

			if (GET_KEYDOWN(KEY_TYPE::ENTER) && m_isDestroy)
			{
				m_isDestroy = false;
				slotReel->DestroyWeapon();
				m_isShooting = true;
				SetStamina(m_maxStamina);
			}

			isCanSlotReel = true;
			if (m_stamina > 0)
			{
				if (GET_KEY(KEY_TYPE::LEFT)) dir.x -= 1.f;
				if (GET_KEY(KEY_TYPE::RIGHT)) dir.x += 1.f;
				//if (GET_KEY(KEY_TYPE::UP)) angle += 0.1f;
				//if (GET_KEY(KEY_TYPE::DOWN)) angle -= 0.1f;
				if (GET_KEYDOWN(KEY_TYPE::RSHIFT))
				{
					rb = GetComponent<Rigidbody>();
					if (rb->IsGrounded())
					{
						AddStamina(-15);
						Jump();
					}
				}
			}

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
	//float prevPosX = GetPos().x;
	//Translate({dir.x * fDT * 200.f, dir.y * fDT * 200.f});
	rb->SetVelocity({ dir.x * 200.f, rb->GetVelocity().y });
	if (dir.x != 0.f) 
		m_isFlipped = dir.x < 0.f;
	//float nextPosX = GetPos().x;
	//if (prevPosX != nextPosX)
	if(rb->GetVelocity().x != 0)
		AddStamina(-0.5f);

	if (slotReel != nullptr)
	{
		slotReel->WeaponFliper(m_isFlipped, playerCount);
	}

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
		&& GET_SINGLE(TurnManager)->GetCurPlayer() == playerCount && isCanSlotReel == true && !health->IsDead())
	{
		m_isDestroy = true;

		isCanSlotReel = false;

		if (slotReel != nullptr)
		{
			GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(slotReel);
			slotReel = nullptr;
		}
	
		slotReel = new SlotReel();
		slotReel->SetSize({ 500, 500 });
	
		slotReel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	
	
		int turnNum = m_turnType == TurnType::Player1 ? 1 : 2;
	
		slotReel->SetSlotRolling(turnNum);
	
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
	PLAY_SOUND(L"PlayerJumpSFX");
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetGrounded(false);
	Vec2 jumpPower{ 0, -50 };
	rb->AddImpulse(jumpPower * 5);
}




