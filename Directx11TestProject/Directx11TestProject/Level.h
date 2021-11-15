#pragma once
#include "Window.h"
#include <fstream>

class Level
{
public:
	Level() = default;
	~Level() = default;

	enum class Map {ONE, TWO, THREE};
	void loadMap(int lvl_map_idx, Window& window);
	void loadMap(Map lvl_map, Window& window);

private:
	std::fstream level_file;
};