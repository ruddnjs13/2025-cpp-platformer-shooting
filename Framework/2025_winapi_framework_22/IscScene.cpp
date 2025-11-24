#include "pch.h"
#include "IscScene.h"
#include "Object.h"
#include "Player.h"

void IscScene::Init()
{
	Spawn<Player>(Layer::PLAYER, { 300, 300 }, { 10, 10 });
}

void IscScene::Update()
{
	Scene::Update();
}
