#pragma once
#include "Object.h"
#include "WeaponHolderComponent.h"
#include "SlotReel.h"
#include <wtypes.h>

class Texture;
class TestPlayer :
    public Object
{
public:
    TestPlayer();
	~TestPlayer();

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

