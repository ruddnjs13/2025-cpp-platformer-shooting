#include "pch.h"
#include "TileMapManager.h"

void TileMapManager::LoadAllMap()
{

	
}

void TileMapManager::LoadMap(wstring mapName, wstring mapFileName)
{
	std::unique_ptr<tson::Map> map = t.parse(mapFileName);

	//maps.insert(std::make_pair);
}

