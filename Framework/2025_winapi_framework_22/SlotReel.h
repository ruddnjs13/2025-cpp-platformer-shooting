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
    void WeaponFliper(bool isFlip , int playerCount);
    void Update() override;
    void Render(HDC _hdc) override;
    void SetRollingTexture(RollingItem* rollItem,wstring textureName, Vec2 offsetPos, float speed);
    void SetStartTexture(RollingItem* rollItem, wstring textureName, Vec2 offsetPos);
    void MakeWeapon(Weapon* targetWeapon, int _playerNum);
    void DestroyWeapon();
    void EnterCollision(Collider* _other)override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;

public:
    void SlotRolling(int _playerNum);
    void SetOffset(Vec2 newOffset) { m_offsetPos = newOffset; }
    Vec2 GetOffset() { return m_offsetPos; }
    Object* GetOwner() { return m_owner; }
    void SetOwner(Object* owner) { m_owner = owner; }
    int GetPlayerNum() { return playerNum; }
    void SetPlayerNum(int _pNum) { playerNum = _pNum; }
    
private:
    int playerNum;
    WeaponHolderComponent* m_pWeaponHolder = nullptr;
    vector<RollingItem*> 
        rollingVec;
    Weapon* selectWeapon;
    Object* m_owner;
    Vec2 m_offsetPos;
    Texture* m_pTex;
};


