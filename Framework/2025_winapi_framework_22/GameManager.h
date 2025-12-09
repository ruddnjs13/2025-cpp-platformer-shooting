#pragma once

class MatchScoreUI;

class GameManager
{
	DECLARE_SINGLE(GameManager)

public:
	void Reset();
	void MatchWin();
	void GameOver(int idx);

	int GetPlayer1Score(){ return player1_Score; }
	int GetPlayer2Score(){ return player2_Score; }

	void SetPlayerDead(int idx);

public:
	int player1_Score;
	int player2_Score;

	bool player1_Die = false;
	bool player2_Die = false;

	MatchScoreUI* matchScoreUI;
};

