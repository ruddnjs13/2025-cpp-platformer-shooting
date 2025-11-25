#include "pch.h"
#include "InputManager.h"
#include "TurnManager.h"
#include "TestWeapon.h"
#include "KmjScene.h"
#include "TestPlayer.h"

void KmjScene::Init()
{
	Object* obj = new TestPlayer;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	AddObject(obj, Layer::PLAYER);

	
	GET_SINGLE(TurnManager)->RaiseEvent(TurnType::Waiting, [this]()
		{
			cout << "Waiting Turn Event Call" << endl;
		});
	GET_SINGLE(TurnManager)->RaiseEvent(TurnType::Select, [this]()
		{
			cout << "Select Turn Event Call" << endl;
		});

	GET_SINGLE(TurnManager)->RaiseEvent(TurnType::Play, [this]()
		{
			cout << "Play Turn Event Call" << endl;
		});

}

void KmjScene::Update()
{


	Scene::Update();



	//if (GET_KEYDOWN(KEY_TYPE::Q))
	//	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Select);
	//if (GET_KEYDOWN(KEY_TYPE::W))
	//	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Play);
	//if (GET_KEYDOWN(KEY_TYPE::E))
	//	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
	

		
}
