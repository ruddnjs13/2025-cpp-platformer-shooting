#pragma once
#include "Object.h"
#include "Texture.h"

class TextureObject;

class Trajectory :
    public Object
{
public:
	Trajectory();
	~Trajectory();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	void ShowAngle(Object* owner);


public:
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

public:
	Object* m_owner;

private:
	float m_angle;
	Vec2 m_dir;
	float m_speed;
};

