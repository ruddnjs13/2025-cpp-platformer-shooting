#include "pch.h"
#include "TurnManager.h"


/// <summary>
/// 턴을 넘겨주는 함수 (플레이어 턴으로 넘어갈떄 Enum값을 Play로 해주세요)
/// </summary>
/// <param name="nextTurn">다음 턴</param>
void TurnManager::ChangeNextTurn(TurnType nextTurn)
{
	m_curTurn = nextTurn;

	switch (m_curTurn)
	{
	case TurnType::Select:
		cout << "Select Scene" << " ";
		break;
	case TurnType::Play:
		cout << "Play Scene" << " ";
		break;
	case TurnType::Waiting:
		cout << "Waiting Scene" << " ";
		break;
	case TurnType::GameEnd:
		cout << "Game End Scene" << " ";
		break;
	case TurnType::Player1:
		cout << "Player 1 Scene" << " ";
		break;
	case TurnType::Player2:
		cout << "Player 2 Scene" << " ";
	default:
		break;
	}

	if (m_curTurn == TurnType::Waiting)
	{
		if (m_curPlayerIdx == 2)
		{
			m_curPlayerIdx = 1;
		}
		else
		{
			m_curPlayerIdx += 1;
		}
	}

	if (m_curTurn == TurnType::Play)
	{
		if (m_curPlayerIdx == 1)
		{
			ChangeNextTurn(TurnType::Player1);
		}
		else if(m_curPlayerIdx == 2)
		{
			ChangeNextTurn(TurnType::Player2);
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
