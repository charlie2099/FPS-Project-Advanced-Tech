#pragma once
#include "Window.h"
#include "Timer.h"
#include "Cube.h"
#include "Enemy.h"
#include "Plane.h"
#include "Constants.h"
#include "Colours.h"
#include "Collision.h"
#include <iostream>
#include <fstream>

class Game
{
public:
	Game();
	int Run();

private:
	void KeyboardInputs(const float& dt);
	void Update();
	void Render();
	void LoadMap();

	Window window;
	Timer timer;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Cube>> bullets;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Plane>> floortiles;
	std::unique_ptr<Cube> spawnpoint;
	//std::vector<std::unique_ptr<Projectile>> bullets;

	Collision collider;

	bool bullet_move = false;
};

