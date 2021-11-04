#pragma once
#include "Window.h"
#include <fstream>

class Level
{
public:
	Level() = default;
	~Level() = default;

	enum class Map {ONE, TWO, THREE};
	void loadMap(int lvl_map_idx, Window& wnd);
	void loadMap(Map lvl_map, Window& wnd);

private:
	std::fstream level_file;
};