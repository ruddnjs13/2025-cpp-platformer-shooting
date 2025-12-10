#include "pch.h"
#include "GameOverScene.h"
#include "Player.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "UIManager.h"

void GameOverScene::Init()
{
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::GameOver);
	pPlayer2 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, {128, 128 });
	pPlayer1 = Spawn<Player>(Layer::PLAYER, { 980, 300 }, { 128, 128 });
	pPlayer1->AddStamina(-1000);
	pPlayer1->AddStamina(-1000);

	pPlayer1->GetComponent<Rigidbody>()->SetUseGravity(false);
	pPlayer2->GetComponent<Rigidbody>()->SetUseGravity(false);
}

void GameOverScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
	pPlayer2->m_pTex->SetFlipped(true);
}
