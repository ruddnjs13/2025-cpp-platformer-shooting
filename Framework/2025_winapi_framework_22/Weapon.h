#pragma once
#include "Texture.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;

private:
	void CreateProjectile();

private:
	Vec2 m_pos;
	Vec2 m_size;
	Texture* m_pTex;
};

