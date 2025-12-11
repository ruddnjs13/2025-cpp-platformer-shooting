#include "pch.h"
#include "LkwScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "DieZone.h"
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


void InGameScene::Init()
{
    GET_SINGLE(UIManager)->SetCanvas(CanvasType::InGame);
    GET_SINGLE(GameManager)->ResetMatch();

    std::wstring mapname = GET_SINGLE(GameManager)->GetMapName();
    GET_SINGLE(TileMapManager)->SetTileMapToScene(this, mapname);
    PLAY_SOUND(mapname + L"BGM");


    DieZone* pDiezone = Spawn<DieZone>(Layer::DEFAULT, { 0, 800 }, { 1000.f, 100.f });
    pPlayer1 = Spawn<Player>(Layer::PLAYER, GET_SINGLE(GameManager)->GetPlayer1Pos(), { 32, 32 });
    pPlayer2 = Spawn<Player>(Layer::PLAYER, GET_SINGLE(GameManager)->GetPlayer2Pos(), {32, 32});
    pPlayer1->SetPlayerTurn(TurnType::Player1, 1);
    pPlayer2->SetPlayerTurn(TurnType::Player2, 2);


    srand(static_cast<unsigned int>(time(nullptr)));

    int randomPlayer = rand() % 2 + 1;

    GET_SINGLE(TurnManager)->SetCurrentPlayer(randomPlayer);

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

    p1DeadHandle = pPlayer1->onDeadEvent.AddListener(
        [](float value) {
            GET_SINGLE(GameManager)->SetPlayerDead(1);
        });
    p2DeadHandle = pPlayer2->onDeadEvent.AddListener(
        [](float value) {
            GET_SINGLE(GameManager)->SetPlayerDead(2);
        });
}

void InGameScene::Update()
{
	Scene::Update();
}

void InGameScene::Release()
{
    GET_SINGLE(ResourceManager)->StopAllSound();
    pPlayer1->onDeadEvent.RemoveListener(p1DeadHandle);
    pPlayer2->onDeadEvent.RemoveListener(p2DeadHandle);

    pPlayer1->GetComponent<Health>()->OnHealthChanged.RemoveListener(p1HealthHandle);
    pPlayer1->OnStaminaChanged.RemoveListener(p1SteminaHandle);
    pPlayer2->GetComponent<Health>()->OnHealthChanged.RemoveListener(p2HealthHandle);
    pPlayer2->OnStaminaChanged.RemoveListener(p2SteminaHandle);
    Scene::Release();
}
