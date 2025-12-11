#include "pch.h"
#include "Texture.h"
#include "GameOverScene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "UIManager.h"

void GameOverScene::Init()
{
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::GameOver);
	PLAY_SOUND(L"GameEndSFX");
	pPlayer2 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, {128, 128 });
	pPlayer1 = Spawn<Player>(Layer::PLAYER, { 980, 300 }, { 128, 128 });

	pPlayer1->SetPlayerTurn(TurnType::Player1,1);
	pPlayer2->SetPlayerTurn(TurnType::Player2,2);

	pPlayer1->SetIsFigures(true);
	pPlayer2->SetIsFigures(true);

	pPlayer1->SetFlipped(true);

	pPlayer1->AddStamina(-1000);
	pPlayer1->AddStamina(-1000);

	pPlayer1->GetComponent<Rigidbody>()->SetUseGravity(false);
	pPlayer2->GetComponent<Rigidbody>()->SetUseGravity(false);
}

void GameOverScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
