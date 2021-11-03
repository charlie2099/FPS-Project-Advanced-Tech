#pragma once
#include "Window.h"
#include "Timer.h"
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
	Timer timer;
};
