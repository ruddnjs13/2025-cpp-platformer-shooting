#pragma once
#include "Object.h"

class Weapon 
	: public Object
{
public:
	Weapon();
	virtual ~Weapon();

public:
	virtual void SetOwner(Object* _owner) { m_owner = _owner; }
	virtual void Update() abstract;
	virtual void Rotate() abstract;
	virtual void Render(HDC _hdc) abstract;
	virtual void Shoot() abstract;

public:
	void SetRotation(Vec2 _angle);
	Vec2 GetAngle() const { return m_angle; }

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

protected:
	Vec2 m_offsetPos;
	bool isShoot = true; 
private:
	Object* m_owner;
	Vec2 m_angle;
	Vec2 m_pos;
	Vec2 m_size;
};

