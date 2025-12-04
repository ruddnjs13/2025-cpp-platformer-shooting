#include "pch.h"
#include "TileMapManager.h"
#include "ResourceManager.h"
#include "Tile.h"
#include <filesystem>


void TileMapManager::LoadAllTileMap()
{
	LoadTileMap(L"Map1", "Resource/Map/Map1.txt");
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
				tile->SetCollSize({ TILE_WIDTH / 2,TILE_HEIGHT });
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Trunk_Right)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Trunk_Right"));
				tile->SetCollSize({ TILE_WIDTH / 2,TILE_WIDTH });
			}
			else if (maps[mapName]->map[i][j] == (char)TileType::Leaves)
			{
				tile = new Tile(GET_SINGLE(ResourceManager)->GetTexture(L"Leaves"));
			}

			if (tile != nullptr)
			{
				tile->SetPos({TILE_WIDTH / 2 + TILE_WIDTH * j, TILE_HEIGHT * i });
				tile->SetSize({ TILE_WIDTH,TILE_HEIGHT });
				targetScene->AddObject(tile, Layer::DEFAULT);
			}
		}
	}
}

