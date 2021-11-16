#pragma once
#include "Window.h"
#include "Timer.h"
#include "Cube.h"
#include "Enemy.h"
#include "Plane.h"
#include "Constants.h"
#include "Colours.h"
#include <iostream>
#include <fstream>

class Game
{
public:
	Game();
	int Run();

private:
	void Update();
	void Render();
	void KeyboardInputs(const float& dt);
	void LoadMap();

	Window window;
	Timer timer;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Plane>> planes;
	//std::unique_ptr<Cube> test;
};

