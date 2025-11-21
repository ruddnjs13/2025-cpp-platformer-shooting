#include "pch.h"
#include "TurnManager.h"


/// <summary>
/// 턴을 넘겨주는 함수 (플레이어 턴으로 넘어갈떄 Play이넘값으로 해주세요)
/// </summary>
/// <param name="nextTurn"></param>
void TurnManager::ChangeNextTurn(TurnType nextTurn)
{
	m_curTurn = nextTurn;

	if (m_curTurn == TurnType::Play)
	{
		if (m_curPlayerIdx == 1)
		{
			m_curTurn = TurnType::Player1;
		}
		else if(m_curPlayerIdx == 2)
		{
			m_curTurn = TurnType::Player2;
		}
	}

	if (m_curTurn == TurnType::Waiting)
	{
		if (m_curPlayerIdx > 2)
		{
			m_curPlayerIdx = 1;
		}
		else
		{
			m_curPlayerIdx += 1;
		}
	}
}

/// <summary>
/// 현재 턴을 반환하는 함수
/// </summary>
/// <returns></returns>
TurnType TurnManager::GetCurTurn()
{
	return m_curTurn;
}

void TurnManager::WaitingTurnUpdate()
{
	if (m_curTurn == TurnType::Waiting)
	{
		float waitTime = GET_SINGLE(TimeManager)->GetDT();

		if (waitTime >= 2.f)
			ChangeNextTurn(TurnType::Select);
	}
}
