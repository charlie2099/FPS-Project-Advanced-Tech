#pragma once
#include "Window.h"
#include "Camera.h"
#include "Timer.h"
//#include "Level.h"
#include "Cube.h"
#include <fstream>

class Game
{
public:
	Game();
	int Run();

private:
	void Update();
	void KeyInputs(const float& dt);

	Window wnd;
	Camera camera;
	Timer timer;
	//Level level;
	std::unique_ptr<Cube> cube;
	std::unique_ptr<Cube> level_block;
	//std::vector<std::unique_ptr<Cube>> level_blocks;

	float speed_factor = 1.0f;
};
