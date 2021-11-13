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

	Window wnd;
	Camera camera;
	Timer timer;
	//Level level;
	std::unique_ptr<Cube> cube;
	//std::unique_ptr<Cube> cube2;

	float speed_factor = 1.0f;
};
