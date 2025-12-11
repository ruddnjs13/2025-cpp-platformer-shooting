#pragma once
#include "Object.h"

class Bullet 
	: public Object
{
public:
	Bullet();
	~Bullet();

public:
	virtual void Update() abstract;
	virtual void Render(HDC _hdc) abstract;
	virtual void BurstBullet() abstract;	
	virtual void Rotate() abstract;
	virtual void DestoyThis() abstract;
	virtual void DestroyOther(Collider* _other) abstract;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;


public:
	void SetDamage(float _damage) { m_damage = _damage; }
	void SetSpeed(float _speed) { m_speed = _speed; }
	void SetAngle(float _angle)
	{
		m_angle = _angle;
	}
	void SetDir(Vec2 _dir)
	{
		m_dir = _dir;
		m_dir.Normalize();
	}

	void SetAngleValue(float angle) { m_angleValue = angle; }

	void SetFlip(bool _isFlip) { isFlip = _isFlip; }
	void SetPlayer(bool playerCnt) { m_playerCount = playerCnt; }
public:
	float destoryTime = 0;
	bool isFlip = false;
	int m_playerCount = 0;
	float m_angleValue = 0;
	float m_angle;
	float m_speed = 500; 

protected:
	Vec2 m_dir;
	float m_damage;
};

