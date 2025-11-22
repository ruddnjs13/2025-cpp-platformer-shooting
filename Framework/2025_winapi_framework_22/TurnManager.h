#pragma once
class TurnManager
{
	DECLARE_SINGLE(TurnManager);

public:
	void ChangeNextTurn(TurnType nextTurn);
	TurnType GetCurTurn();
	void WaitingTurnUpdate();


private:
	int m_curPlayerIdx = 0;
	float m_waitTimer = 0;
	TurnType m_curTurn = TurnType::Select;
};

