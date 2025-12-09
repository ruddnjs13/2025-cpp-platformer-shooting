#pragma once
#include "Object.h"
#include "TurnManager.h"
#include "MyAction.h"


class SlotReel;
class Texture;
class Player :
    public Object
{
public:
	Player();
	~Player();
public:
	MyAction<float> OnStaminaChanged;
	//virtual void Update();
	//virtual void Render(HDC _hdc);
	void SetStamina(float _stamina) { m_maxStamina = _stamina;  m_stamina = _stamina; }
	void AddStamina(float _delta)
	{
		m_stamina += _delta;
		if (m_stamina < 0.f) m_stamina = 0.f;
		if (m_stamina > m_maxStamina) m_stamina = m_maxStamina;
		OnStaminaChanged.Invoke(m_stamina);
	}
	const float GetStamina() const { m_stamina; }
	const bool IsFlipped() const { return m_isFlipped; }
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void ChangeState(PlayerState _newState);
	void SetPlayerTurn(TurnType _turnType, int _playerCount)
	{
		if (_turnType != TurnType::Player1 && _turnType != TurnType::Player2)
		{
			std::cout << "플레이어가 잘못된 턴 타입을 받음!" << endl;
			return;
		}
		m_turnType = _turnType; 
		playerCount = _playerCount;

	}
	void SetWeaponCount(int count) { weaponCount = count; }
private:
	void CreateProjectile();
	bool CheckPlayerTurn(TurnType _checkType)
	{
		TurnType curTurn = GET_SINGLE(TurnManager)->GetCurrentTurn();

		return curTurn == m_turnType && m_turnType == _checkType;
	}
	void Jump();
	void StartSlotRell();
public:
	int playerCount = 0;
	bool isCanSlotReel = true;
private:	

	int weaponCount = 0;
	float m_stamina = 0;
	float m_maxStamina = 0;
	bool m_isFlipped = false;
	bool m_isDestroy = false;
	SlotReel* slotReel = nullptr;
	Texture* m_pTex;
	TurnType m_turnType;
	PlayerState m_state;
	PlayerState m_prevState;
	MyAction<int> onDeadEvent;
};

