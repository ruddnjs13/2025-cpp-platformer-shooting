#include "pch.h"
#include "IscScene.h"
#include "Object.h"
#include "Player.h"
#include "TurnManager.h"
#include "Floor.h"
#include "CollisionManager.h"3

void IscScene::Init()
{	
	Player* pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 300 }, { 28, 28 });
	Player* pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 500 }, { 28, 28 });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 600 }, { 1000.f,100.f });
	Spawn<Floor>(Layer::DEFAULT, { 700, 550 }, { 32, 32 });
	cout << "아아아ㅣ아ㅣ아ㅏ아앙" << endl;
	pPlayer1->SetPlayerTurn(TurnType::Player1, 1);
	pPlayer2->SetPlayerTurn(TurnType::Player2, 2);
	
	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Player2);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::PLAYER);
}

void IscScene::Update()
{
	Scene::Update();
}
