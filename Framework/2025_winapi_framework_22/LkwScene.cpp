#include "pch.h"
#include "LkwScene.h"
#include "UIManager.h"

void LkwScene::Init()
{
	cout << "씬 변경후 초기화";
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);

}

void LkwScene::Update()
{
	Scene::Update();
}
