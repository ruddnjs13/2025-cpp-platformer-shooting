#pragma once
#include "tileson.hpp"

tson::Tileson t;


class TileMapManager
{
private:
	std::unordered_map<wstring, std::unique_ptr<tson::Map>> maps;
public:
	void LoadAllMap();
	void LoadMap(wstring mapName, wstring mapFileName);
};

