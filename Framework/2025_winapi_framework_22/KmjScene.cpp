#include "pch.h"
#include "InputManager.h"
#include "TurnManager.h"
#include "KmjScene.h"

void KmjScene::Init()
{
}

void KmjScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::ENTER))
	{
		GET_SINGLE(TurnManager)->ChangeNextTurn(TurnType::Waiting);
	}

	if(GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		GET_SINGLE(TurnManager)->ChangeNextTurn(TurnType::Play);
	}

}
