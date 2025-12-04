#pragma once
#include "Object.h"
#include "SlotReel.h"

class Texture;
class TestPlayer2 :
    public Object
{
public:
	TestPlayer2();
	~TestPlayer2();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void SetWeaponCount(int count) { weaponCount = count; }

private:
	int weaponCount = 0;

	SlotReel* slotReel = nullptr;


	Texture* m_pTex = nullptr;
};

