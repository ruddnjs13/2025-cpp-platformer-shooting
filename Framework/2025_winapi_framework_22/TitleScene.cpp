#include "pch.h"
#include "TitleScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "ResourceManager.h"
#include "Background.h"

TitleScene::~TitleScene()
{
	GET_SINGLE(ResourceManager)->StopAllSound();
	Scene::~Scene();
}

void TitleScene::Init()
{
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);
	PLAY_SOUND(L"TitleBGM");
	
}
