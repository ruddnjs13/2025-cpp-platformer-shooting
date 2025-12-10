#pragma once
#include "TileMap.h"
#include "Scene.h"

class TileMapManager
{
	DECLARE_SINGLE(TileMapManager)
public:
	std::map<wstring, TileMap*> maps;
public:
	void Release();
	void LoadAllTileMap();
	void LoadTileMap(wstring mapName, std::string fileName);

	void SetTileMapToScene(Scene* targetScene, wstring mapName);
};
