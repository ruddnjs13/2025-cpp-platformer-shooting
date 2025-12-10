#include "pch.h"
#include "TitleScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "ResourceManager.h"
#include "Background.h"

void TitleScene::Init()
{
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);
	//GET_SINGLE(TileMapManager)->SetTileMapToScene(this, L"Map1");
	//Background* background = Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });
	//background->Init(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));

	//AddObject(background, Layer::BACKGROUND);
}
