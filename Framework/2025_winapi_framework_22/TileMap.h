#pragma once
#include <fstream>

class TileMap
{
public:
	TileMap();
	~TileMap();

public:
	char map[MAP_HEIGHT][MAP_WIDTH];
public:
	void LoadMap(std::string mapFileName);
};

