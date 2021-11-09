#pragma once
#include "Window.h"
#include "Camera.h"
#include "Timer.h"
//#include "Level.h"
#include "Cube.h"
#include <fstream>
#include <random>

class Game
{
public:
	Game();
	int Run();

private:
	void Update();

	Window wnd;
	Camera camera;
	//Level level;
	Timer timer;

	std::vector<std::unique_ptr<class Cube>> cubes;
	float speed_factor = 1.0f;
};
