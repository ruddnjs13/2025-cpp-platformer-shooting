#include "pch.h"
#include "InputManager.h"
#include "TurnManager.h"
#include "TestWeapon.h"
#include "KmjScene.h"
#include "TestPlayer.h"
#include "TestPlayer2.h"
#include "Floor.h"
#include "CollisionManager.h"

void KmjScene::Init()
{

	Object* obj = new TestPlayer;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	AddObject(obj, Layer::PLAYER);

	Object* obj2 = new TestPlayer2;
	obj2->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj2->SetSize({ 100.f, 100.f });
	AddObject(obj2, Layer::PLAYER);


	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 600 }, { 100.f,100.f });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::Boom, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::Slot, Layer::RollItem);
}

void KmjScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::Q))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Select);
	if (GET_KEYDOWN(KEY_TYPE::W))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Play);
	if (GET_KEYDOWN(KEY_TYPE::E))
		GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
}
