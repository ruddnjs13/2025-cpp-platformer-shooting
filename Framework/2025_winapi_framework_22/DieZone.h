#pragma once
#include "Object.h"

class DieZone
	: public Object
{
public:
	DieZone();
	~DieZone();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other) override;
};

