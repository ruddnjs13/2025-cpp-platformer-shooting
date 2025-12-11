#pragma once

class MatchScoreUI;

class GameManager
{
	DECLARE_SINGLE(GameManager)

public:
	void ResetMatch();
	void ResetGame();
	void Reset();
	bool MatchWin();
	void GameOver();

	int GetPlayer1Score(){ return player1_Score; }
	int GetPlayer2Score(){ return player2_Score; }

	void SetPlayerDead(int idx);

	void SetMatchScoreUI(MatchScoreUI* matchscoreUI);

	wstring GetMapName();

	Vec2 GetPlayer1Pos();
	Vec2 GetPlayer2Pos();

public:
	int player1_Score = 0;
	int player2_Score = 0;

	bool player1_Die = false;
	bool player2_Die = false;

	MatchScoreUI* matchScoreUI;
private:
	wstring mapNames[3] = { L"Map1",L"Map2", L"Map3" };
	Vec2 p1_spawnPos[3] = { {330,300},{400,500},{250,550} };
	Vec2 p2_spawnPos[3] = { {1070,300},{880,500},{1230,220} };
	int mapIdx = 0;
};

