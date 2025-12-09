#pragma once
#include "Component.h"
class Collider :
    public Component
{
public:
    Collider();
    ~Collider();
public:
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC _hDC) override;
public:
    void EnterCollision(Collider* _other); // 충돌진입
    void StayCollision(Collider* _other); // 충돌중
    void ExitCollision(Collider* _other); // 충돌해제
public:
    UINT GetID() const { return m_ID; }
    void SetSize(Vec2 _size) { m_size = _size; }
    const Vec2& GetSize() const { return m_size; }
    void SetOffSetPos(Vec2 _OffsetPos)
    {
        m_offsetPos = _OffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_offsetPos; }
    const Vec2& GetUpdatedPos() const
    {
        return m_updatedPos;
    }
    const int GetGroundCollCnt() const { return m_groundCollCnt; }
    const void AddGroundCollCnt(int _cnt)
    {
        m_groundCollCnt += _cnt;

        if (m_groundCollCnt < 0) m_groundCollCnt = 0;
    }
    void SetName(const wstring& n) { m_name = n; }
    const wstring& GetName() const { return m_name; }

    void SetTrigger(bool t) { m_isTrigger = t; }
    bool IsTrigger() const { return m_isTrigger; }

private:
    wstring m_name;   // 콜라이더 식별용 이름
    bool m_isTrigger = false;

    Vec2 m_size; // 콜라이더 크기
    // Object로부터 상대적인 위치
    Vec2 m_offsetPos;
    // LateUpdate에서 매 프레임마다 오브젝트로부터 계산되는 위치
    Vec2 m_updatedPos;
    UINT m_ID; // 충돌체 고유 id 값
    static UINT m_nextID;
    bool m_showDebug;

    int m_groundCollCnt = 0; // 현재 자신의 바닥에 있는 충돌체 개수
};