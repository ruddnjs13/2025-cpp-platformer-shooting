#pragma once
#include <fstream>

class TileMap
{
public:
	char map[MAP_HEIGHT][MAP_WIDTH];
public:
	void LoadMap(char map[MAP_HEIGHT][MAP_WIDTH], std::string mapFileName);
};

