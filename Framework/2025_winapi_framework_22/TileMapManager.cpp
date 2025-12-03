#include "pch.h"
#include "TileMapManager.h"
#include "ResourceManager.h"
#include "Tile.h"

void TileMapManager::LoadAllTileMap()
{
	LoadTileMap(L"Map1", "D:/github/2025-cpp-platformer-shooting/Framework/Output/build/Resource/Map/Map1.txt");
}

void TileMapManager::LoadTileMap(wstring mapName, std::string fileName)
{
	TileMap* map = new TileMap();

	map->LoadMap(fileName);

	maps.insert(std::make_pair(mapName,map));
}

void TileMapManager::SetRandomTileMapToScene(Scene* targetScene)
{
	wstring mapName = L"Map1";

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			Tile* tile = nullptr;
			if (maps[mapName]->map[i][j] == (char)TileType::Ground)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Ground"));
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Grass)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Grass"));
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Trunk_Left)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Trunk_Left"));
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Trunk_Right)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Trunk_Right"));
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Leaves)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Leaves"));
			}

			if (tile != nullptr)
			{
				tile->SetPos({ 16 + 32 * j,16 + 32 * i });
				tile->SetSize({ 32,32 });
				targetScene->AddObject(tile, Layer::DEFAULT);
			}
		}
	}
}

