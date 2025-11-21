#pragma once
class TurnManager
{
	DECLARE_SINGLE(TurnManager);

public:
	void ChangeNextTurn(TurnType nextTurn);
	TurnType GetCurTurn();
	int GetCurPlayerTurn();

private:
	void WaitingTurnUpdate();


private:
	int m_curPlayerIdx = 0;
	int m_waitTimer = 0;
	TurnType m_curTurn = TurnType::Select;
};

