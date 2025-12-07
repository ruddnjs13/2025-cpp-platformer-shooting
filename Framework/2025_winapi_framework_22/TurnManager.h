#pragma once
#include "MyAction.h"
#include <map>


class TurnManager
{
    DECLARE_SINGLE(TurnManager);
public:

    void RaiseEvent(TurnType _turn, Action _callback);
    void ChangeTurn(TurnType _nextTurn);
	TurnType GetCurrentTurn() const { return m_curTurn; }
    void ClearEvents();
    int GetCurPlayer() { return m_CurPlayer; }
    void SendTurnName();
private:
    void Invoke(TurnType _turn);
    void ChangingTurnCondition();
    void WaitingTurnUpdate();

public:
    MyAction<void> turnEvt;
private:
    std::map<TurnType, std::vector<Action>> m_eventMap;
	TurnType m_curTurn = TurnType::Waiting;
	int m_CurPlayer = 0;
	float m_waitTimer = 0.f;
};
