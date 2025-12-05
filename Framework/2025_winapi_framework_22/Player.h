#pragma once
#include "Object.h"
#include "TurnManager.h"

class SlotReel;
class Texture;
class Player :
    public Object
{
public:
	Player();
	~Player();
public:
	//virtual void Update();
	//virtual void Render(HDC _hdc);
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void ChangeState(PlayerState _newState);
	void SetPlayerTurn(TurnType _turnType) 
	{
		if (_turnType != TurnType::Player1 && _turnType != TurnType::Player2)
		{
			std::cout << "플레이어가 잘못된 턴 타입을 받음!" << endl;
			return;
		}
		m_turnType = _turnType; 
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
private:

	int weaponCount = 0;

	SlotReel* slotReel = nullptr;
	Texture* m_pTex;
	TurnType m_turnType;
	PlayerState m_state;
	PlayerState m_prevState;

	int collCnt = 0;
};

