#include "pch.h"
#include "TurnManager.h"

void TurnManager::ChangeNextTurn(TurnType nextTurn)
{
	m_curTurn = nextTurn;

	if (nextTurn == TurnType::Waiting)
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

int TurnManager::GetCurPlayerTurn()
{
	return m_curPlayerIdx;
}

void TurnManager::WaitingTurnUpdate()
{
	if (m_curTurn == TurnType::Waiting)
	{
		float waitTime = GET_SINGLE(TimeManager)->GetDT();

		if(waitTime >= 2.f)
			m_curTurn = TurnType::Select;
	}
}
