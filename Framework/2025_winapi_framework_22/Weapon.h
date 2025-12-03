#pragma once
#include "Object.h"


class WeaponTrajectory;

class Weapon 
	: public Object
{
public:
	Weapon();
	~Weapon();

public:
	void Update() override;
	void Render(HDC _hdc) override;

public:
	void SetRotation(Vec2 _angle);
	void SetOwner(Object* _owner) { m_owner = _owner; }
	//Vec2 GetAngle() const { return m_angle; }

	void SetPos(Vec2 _pos) { m_pos = _pos; }
	void SetSize(Vec2 _size) { m_size = _size; }

	const Vec2& GetPos() const { return m_pos; }
	const Vec2& GetSize()const { return m_size; }
	void SetOffSetPos(Vec2 _OffsetPos)
	{
		m_offsetPos = _OffsetPos;
	}
	const Vec2& GetOffSetPos() const { return m_offsetPos; }
	const Vec2& GetUpdatedPos() const
	{
		return m_pos;
	}
	Object* GetOwner()  { return m_owner; }

	void SetShootAngle(float angle);

protected:
	Vec2 m_offsetPos;
	bool isShoot = true; 
	Vec2 m_angle;
	WeaponTrajectory* m_weaponTrajectory;
private:
	Object* m_owner;
	Vec2 m_pos;
	Vec2 m_size;
};

