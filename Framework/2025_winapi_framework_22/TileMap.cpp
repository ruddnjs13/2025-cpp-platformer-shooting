#include "pch.h"
#include "TileMap.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::LoadMap(std::string mapFileName)
{

	std::ifstream mapFile(mapFileName);

	if (mapFile.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			mapFile.getline(map[i], MAP_WIDTH);
		}
		mapFile.close();
		return;
	}
}
