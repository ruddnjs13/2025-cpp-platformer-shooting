#include "pch.h"
#include "TitleScene.h"
#include "UIManager.h"
#include "TileMapManager.h"
#include "ResourceManager.h"

void TitleScene::Init()
{
	GET_SINGLE(UIManager)->SetCanvas(CanvasType::Title);
	GET_SINGLE(TileMapManager)->SetRandomTileMapToScene(this);

}
