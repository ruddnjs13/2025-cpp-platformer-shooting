#include "pch.h"
#include "TurnManager.h"
#include <iostream>


/// <summary>
/// 원하는 턴에 이벤트를 구독시켜주는 함수
/// </summary>
/// <param name="_turn">구독할 턴</param>
/// <param name="_callback">구독할 함수</param>
void TurnManager::RaiseEvent(TurnType _turn, Action _callback)
{
	m_eventMap[_turn].push_back(_callback);
}

/// <summary>
/// 턴을 바쭤주는 코드(자동으로 해당 턴의 이벤트를 실행시켜줌)
/// </summary>
/// <param name="_nextTurn">바꿀 턴</param>
void TurnManager::ChangeTurn(TurnType _nextTurn)
{
	m_curTurn = _nextTurn;
	Invoke(m_curTurn);
}


/// <summary>
/// 이벤트 구독을 모두 해제하는 코드
/// </summary>
/// <param name="_turn"></param>
void TurnManager::ClearEvents(TurnType turn)
{
    for (auto& events : m_eventMap)
    {
        events.second.clear();
    }

    m_eventMap.clear();
}


/// <summary>
/// 이벤트를 실행시켜주는 코드
/// </summary>
/// <param name="_turn">이벤트를 실행시킬 턴</param>
void TurnManager::Invoke(TurnType _turn)
{
    auto _turnType = m_eventMap.find(_turn);

    if (_turnType == m_eventMap.end())
        return;

    for (auto& callback : _turnType->second)
    {
        if (callback)
            callback();
    }
}

