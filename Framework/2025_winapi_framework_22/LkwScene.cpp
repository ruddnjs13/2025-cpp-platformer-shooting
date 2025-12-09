#include "pch.h"
#include "LkwScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "Player.h"
#include "Floor.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Background.h"
#include "InputManager.h"
#include "InGameCanvas.h"
#include "GameManager.h"
#include "Health.h"
#include "Slider.h"



void LkwScene::Init()
{
    GET_SINGLE(UIManager)->SetCanvas(CanvasType::InGame);
    GET_SINGLE(GameManager)->Reset();

    GET_SINGLE(TileMapManager)->SetTileMapToScene(this, L"Map1");

    pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 300 }, { 32, 32 });
    pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 32, 32 });
    pPlayer1->SetPlayerTurn(TurnType::Player1, 1);
    pPlayer2->SetPlayerTurn(TurnType::Player2, 2);

    GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);

    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::Boom, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::Slot, Layer::RollItem);

    Background* background = Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });
    background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));

    auto curCanvas = UIManager::GetInst()->GetCurCanvas();
    auto inGameCanvas = std::dynamic_pointer_cast<InGameCanvas>(curCanvas);

    if (inGameCanvas)
    {
        p1HealthHandle = pPlayer1->GetComponent<Health>()->OnHealthChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p1_HpBar)
                    inGameCanvas->p1_HpBar->SetValue(value);
            });

        p2HealthHandle =  pPlayer2->GetComponent<Health>()->OnHealthChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p2_HpBar)
                    inGameCanvas->p2_HpBar->SetValue(value);
            });

        p1SteminaHandle = pPlayer1->OnStaminaChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p1_SteminaBar)
                    inGameCanvas->p1_SteminaBar->SetValue(value);
            });

        p2SteminaHandle = pPlayer2->OnStaminaChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p2_SteminaBar)
                    inGameCanvas->p2_SteminaBar->SetValue(value);
            });
    }


}


void LkwScene::Update()
{
   
    
	Scene::Update();
}

void LkwScene::Release()
{
    pPlayer1->GetComponent<Health>()->OnHealthChanged.RemoveListener(p1HealthHandle);
    pPlayer1->OnStaminaChanged.RemoveListener(p1SteminaHandle);
    pPlayer2->GetComponent<Health>()->OnHealthChanged.RemoveListener(p2HealthHandle);
    pPlayer2->OnStaminaChanged.RemoveListener(p2SteminaHandle);
    Scene::Release();
}
