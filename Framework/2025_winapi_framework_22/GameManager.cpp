#include "pch.h"
#include "GameManager.h"
#include "UIManager.h"
#include "MatchScoreUI.h"
#include "SceneManager.h"

void GameManager::ResetMatch()
{
	player1_Die = false;
	player2_Die = false;
}

void GameManager::ResetGame()
{
	player1_Die = false;
	player2_Die = false;
	player1_Score = 0;
	player2_Score = 0;
}

bool GameManager::MatchWin()
{
	bool isGameOver = false;
	if (!player1_Die && !player2_Die) return false;
	else if (player1_Die && !player2_Die)
	{
		player2_Score++;
		isGameOver = true;
	}
	else if(!player1_Die && player2_Die)
	{
		player1_Score++;
		isGameOver = true;
	}
	else if (player1_Die && player2_Die)
	{
		isGameOver = true;
	}

	if(!isGameOver)
		matchScoreUI->SetScore(player1_Score, player2_Score);
	return true;
}

void GameManager::GameOver()
{
	if (player1_Score >= 3 || player2_Score >= 3)
	{
		GET_SINGLE(SceneManager)->RequestLoadScene(L"GameOverScene");
	}
	else
	{
		GET_SINGLE(SceneManager)->RequestLoadScene(L"LkwScene");
	}
}

void GameManager::SetPlayerDead(int idx)
{
	if (idx == 1)
		player1_Die = true;
	else
		player2_Die = true;
}

void GameManager::SetMatchScoreUI(MatchScoreUI* matchscoreUI)
{
	matchScoreUI = matchscoreUI;
	matchScoreUI->SetScore(player1_Score, player2_Score);
}

