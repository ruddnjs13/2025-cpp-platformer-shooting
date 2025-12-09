#pragma once

class MatchScoreUI;

class GameManager
{
	DECLARE_SINGLE(GameManager)

public:
	void Reset();
	bool MatchWin();
	void GameOver();

	int GetPlayer1Score(){ return player1_Score; }
	int GetPlayer2Score(){ return player2_Score; }

	void SetPlayerDead(int idx);

	void SetMatchScoreUI(MatchScoreUI* matchscoreUI);

public:
	int player1_Score = 0;
	int player2_Score = 0;

	bool player1_Die = false;
	bool player2_Die = false;

	MatchScoreUI* matchScoreUI;
};

