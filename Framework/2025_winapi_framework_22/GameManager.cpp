#include "pch.h"
#include "GameManager.h"
#include "UIManager.h"
#include "MatchScoreUI.h"
#include "SceneManager.h"

void GameManager::Reset()
{
	player1_Die = false;
	player2_Die = false;
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
	else if(!player1_Die && player1_Die)
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
	GET_SINGLE(SceneManager)->LoadScene(L"LkwScene");
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

