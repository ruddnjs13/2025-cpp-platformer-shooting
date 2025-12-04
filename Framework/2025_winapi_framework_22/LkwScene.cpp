#include "pch.h"
#include "LkwScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "Player.h"
#include "Floor.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Background.h"


void LkwScene::Init()
{
	//GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::InGame);
	GET_SINGLE(TileMapManager)->SetRandomTileMapToScene(this);

	Player* pPlayer1 = Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 100, 100 });
	Player* pPlayer2 = Spawn<Player>(Layer::PLAYER, { 500, 500 }, { 100, 100 });
	pPlayer1->SetPlayerTurn(TurnType::Player1);
	pPlayer2->SetPlayerTurn(TurnType::Player2);

	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Player1);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);



	Background* background = Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });

	background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));
	

}

void LkwScene::Update()
{
	Scene::Update();
}
