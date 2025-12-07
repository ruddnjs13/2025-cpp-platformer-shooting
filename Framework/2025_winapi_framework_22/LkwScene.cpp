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



void LkwScene::Init()
{
	//GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::InGame);
	GET_SINGLE(TileMapManager)->SetTileMapToScene(this, L"Map1");

	Player* pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 32, 32 });
	Player* pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 300 }, { 32, 32 });
	pPlayer1->SetPlayerTurn(TurnType::Player1, 1);
	pPlayer2->SetPlayerTurn(TurnType::Player2, 2);


	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::Boom, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::Slot, Layer::RollItem);

	Background* background = Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });

	background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));

	auto curCanvas = UIManager::GetInst()->GetCurCanvas();
	auto inGameCanvas = std::dynamic_pointer_cast<InGameCanvas>(curCanvas);

	pPlayer1->GetComponent<Health>()->OnHealthChanged.AddListener(
		std::bind(&Slider::SetValue, inGameCanvas->p1_HpBar, std::placeholders::_1));

	pPlayer2->GetComponent<Health>()->OnHealthChanged.AddListener(
		std::bind(&Slider::SetValue, inGameCanvas->p2_HpBar, std::placeholders::_1));
}

void LkwScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::Q))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Select);
	if (GET_KEYDOWN(KEY_TYPE::W))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Play);
	if (GET_KEYDOWN(KEY_TYPE::E))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
}
