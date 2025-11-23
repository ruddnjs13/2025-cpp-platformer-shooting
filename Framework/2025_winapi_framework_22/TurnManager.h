#pragma once
#include <functional>
#include <map>


class TurnManager
{
public:

    void RaiseEvent(TurnType _turn, Action _callback);
    void ChangeTurn(TurnType _nextTurn);
	TurnType GetCurrentTurn() const { return m_curTurn; }
    void ClearEvents(TurnType turn);
private:
    void Invoke(TurnType _turn);
private:
    std::map<TurnType, std::vector<Action>> m_eventMap;
	TurnType m_curTurn = TurnType::Select;
};
