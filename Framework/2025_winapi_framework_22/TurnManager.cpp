#include "pch.h"
#include "TurnManager.h"

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
