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
#include "Health.h"
#include "Slider.h"



void LkwScene::Init()
{
    //cout << "dddd";
    // Canvas 세팅
    GET_SINGLE(UIManager)->SetCanvas(CanvasType::InGame);

    // TileMap 세팅
    GET_SINGLE(TileMapManager)->SetTileMapToScene(this, L"Map1");

    // 플레이어 생성
    Player* pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 300 }, { 32, 32 });
    Player* pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 32, 32 });
    pPlayer1->SetPlayerTurn(TurnType::Player1, 1);
    pPlayer2->SetPlayerTurn(TurnType::Player2, 2);

    // 초기 턴 설정
    GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);

    // 충돌 레이어 세팅
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::Boom, Layer::DEFAULT);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::Slot, Layer::RollItem);

    // 배경 생성
    Background* background = Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });
    background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));

    auto curCanvas = UIManager::GetInst()->GetCurCanvas();
    auto inGameCanvas = std::dynamic_pointer_cast<InGameCanvas>(curCanvas);

    if (inGameCanvas) // Canvas가 정상적으로 Init된 경우에만 바인딩
    {
        // Player1 HP
        pPlayer1->GetComponent<Health>()->OnHealthChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p1_HpBar)
                    inGameCanvas->p1_HpBar->SetValue(value);
            });

        // Player2 HP
        pPlayer2->GetComponent<Health>()->OnHealthChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p2_HpBar)
                    inGameCanvas->p2_HpBar->SetValue(value);
            });

        // Player1 Stamina
        pPlayer1->OnStaminaChanged.AddListener(
            [inGameCanvas](float value)
            {
                if (inGameCanvas && inGameCanvas->p1_SteminaBar)
                    inGameCanvas->p1_SteminaBar->SetValue(value);
            });

        // Player2 Stamina
        pPlayer2->OnStaminaChanged.AddListener(
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
