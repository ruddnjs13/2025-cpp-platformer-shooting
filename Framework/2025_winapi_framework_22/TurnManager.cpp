    #include "pch.h"
    #include "TurnManager.h"
    #include <iostream>
#include "WindManager.h"
#include "GameManager.h"
#include <thread>


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
    /// 턴을 바꿔주는 코드(자동으로 해당 턴의 이벤트를 실행시켜줌)
    /// </summary>
    /// <param name="_nextTurn">바꿀 턴</param>
    void TurnManager::ChangeTurn(TurnType _nextTurn)
    {
	    m_curTurn = _nextTurn;

        turnEvt.Invoke();
        
        ChangingTurnCondition();

	    Invoke(m_curTurn);

        srand(static_cast<unsigned>(time(nullptr)));

        int randomInt = (rand() % 4001) - 2000;

        GET_SINGLE(WindManager)->SetWind(randomInt);

    }

    void TurnManager::ChangingTurnCondition()
    {
        if (m_curTurn == TurnType::TurnEnd)
        {
            std::thread([this]()
                {
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    ChangeTurn(TurnType::Waiting);
                }).detach();
        }
        if (m_curTurn == TurnType::Waiting)
        {
            m_waitTimer = 0;

            WaitingTurnUpdate();

            if (m_CurPlayer == 2)
            {
                m_CurPlayer = 1;
            }
            else
            {
                m_CurPlayer += 1;
            }
        }
        if (m_curTurn == TurnType::Play)
        {
            if (m_CurPlayer == 1)
            {
                ChangeTurn(TurnType::Player1);
            }
            else if (m_CurPlayer == 2)
            {
                ChangeTurn(TurnType::Player2);
            }
        }
    }

    void TurnManager::WaitingTurnUpdate()
    { 
        std::thread([this]() 
            {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            if (GET_SINGLE(GameManager)->MatchWin())
            {
                GET_SINGLE(GameManager)->GameOver();
            }
            ChangeTurn(TurnType::Select); 
            }).detach();
    }

    /// <summary>
    /// 이벤트 구독을 모두 해제하는 코드
    /// </summary>
    /// <param name="_turn"></param>
    void TurnManager::ClearEvents()
    {
        for (auto& events : m_eventMap)
        {
            events.second.clear();
        }

        m_eventMap.clear();
    }

    void TurnManager::SendTurnName()
    {
        switch (m_curTurn)
        {
        case TurnType::Select:
            break;
        case TurnType::Play:
            break;
        case TurnType::Waiting:
            break;
        case TurnType::TurnEnd:
            break;
        case TurnType::GameEnd:
            break;
        case TurnType::Player1:
            break;
        case TurnType::Player2:
            break;
        default:
            break;
        }
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

