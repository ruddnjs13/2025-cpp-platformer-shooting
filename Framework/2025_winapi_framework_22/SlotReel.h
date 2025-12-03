#pragma once
#include "Object.h"
#include "Weapon.h"
#include "RollingItem.h"

class WeaponHolderComponent;
class Texture;

class SlotReel 
    : public Object
{
public:
    SlotReel();
    ~SlotReel();


public:
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other)override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;

public:
    void SlotRolling();
    void SetOffset(Vec2 newOffset) { m_offsetPos = newOffset; }
    Vec2 GetOffset() { return m_offsetPos; }
    Object* GetOwner() { return m_owner; }
    void SetOwner(Object* owner) { m_owner = owner; }

private:
    WeaponHolderComponent* m_pWeaponHolder = nullptr;
    vector<RollingItem*> rollingVec;
    Weapon* selectWeapon;
    Object* m_owner;
    Vec2 m_offsetPos;
    Texture* m_pTex;
};


