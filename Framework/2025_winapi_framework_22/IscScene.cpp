#include "pch.h"
#include "IscScene.h"
#include "Object.h"
#include "Player.h"
#include "TurnManager.h"

void IscScene::Init()
{
	Player* pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 10, 10 });
	Player* pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 500 }, { 10, 10 });
	pPlayer1->SetPlayerTurn(TurnType::Player1);
	pPlayer2->SetPlayerTurn(TurnType::Player2);
	
	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Player1);
}

void IscScene::Update()
{
	Scene::Update();
}
