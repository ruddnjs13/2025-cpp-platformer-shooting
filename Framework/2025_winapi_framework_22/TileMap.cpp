#include "pch.h"
#include "TileMap.h"

void TileMap::LoadMap(char map[MAP_HEIGHT][MAP_WIDTH], std::string mapFileName)
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
	else
	{
		cout << "·Îµå ¾ÈµÊ" << endl;
	}
}
