#pragma once
#include "Window.h"
#include "Camera.h"
#include "Timer.h"
//#include "Level.h"
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
	//Cube cube;

	float speed_factor = 1.0f;
};
