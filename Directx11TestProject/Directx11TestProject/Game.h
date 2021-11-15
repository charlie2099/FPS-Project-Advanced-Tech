#pragma once
#include "Window.h"
#include "Camera.h"
#include "Timer.h"
//#include "Level.h"
#include "Cube.h"
#include "Plane.h"
#include <fstream>

class Game
{
public:
	Game();
	int Run();

private:
	void Update();
	void KeyInputs(const float& dt);

	Window window;
	Camera camera;
	Timer timer;
	//Level level;
	std::unique_ptr<Plane> plane;
	std::unique_ptr<Cube> cube;
	std::unique_ptr<Cube> level_block;

	float speed_factor = 1.0f;
};
