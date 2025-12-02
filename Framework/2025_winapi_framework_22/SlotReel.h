#pragma once
#include "Object.h"
#include "Weapon.h"
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

public:
    Weapon SlotRolling();
    void SetOffset(Vec2 newOffset) { m_offsetPos = newOffset; }
    Vec2 GetOffset() { return m_offsetPos; }
    Object* GetOwner() { return m_owner; }
    void SetOwner(Object* owner) { m_owner = owner; }

private:
    Weapon selectWeapon;
      Object* m_owner;
      Vec2 m_offsetPos;
      Texture* m_pTex;
};


