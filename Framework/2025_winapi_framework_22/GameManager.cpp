#include "pch.h"
#include "GameManager.h"
#include "UIManager.h"
#include "MatchScoreUI.h"

void GameManager::Reset()
{
	player1_Die = false;
	player2_Die = false;
}

bool GameManager::MatchWin()
{
	if (!player1_Die && !player2_Die) return false;

	if (player1_Die && player2_Die)
	{
		GameOver(3);
		return true;
	}
	else if (player1_Die && !player2_Die)
	{
		GameOver(2);
		return true;
	}
	else
	{
		GameOver(1);
		return true;
	}

	matchScoreUI->SetScore(player1_Score, player2_Score);
}

void GameManager::GameOver(int idx)
{
	if (idx == 1)
	{

	}
	else if (idx == 2)
	{

	}
	if (idx == 3)
	{

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

