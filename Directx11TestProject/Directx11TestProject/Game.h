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
	
	int Go();
private:
	void Update();
private:
	Window wnd;
	Camera camera;
	//Level level;
	Timer timer;
};
