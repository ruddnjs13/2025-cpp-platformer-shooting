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


protected:
	void SetDamage(float _damage) { m_damage = _damage; }
	void SetSpeed(float _speed) { m_speed = _speed; }
	void SetPos(Vec2 _pos) { m_pos = _pos; }
	void SetSize(Vec2 _size) { m_size = _size; }
	const Vec2& GetPos() const { return m_pos; }
	const Vec2& GetSize()const { return m_size; }

private:
	float m_damage;
	float m_speed;
	Vec2 m_dir;
	Vec2 m_angle;
	Vec2 m_pos;
	Vec2 m_size;
};

