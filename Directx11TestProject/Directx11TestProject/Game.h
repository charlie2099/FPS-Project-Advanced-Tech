#pragma once
#include "Window.h"
#include "Timer.h"
#include "Cube.h"
#include "Enemy.h"
#include "Plane.h"
#include "Constants.h"
#include "Colours.h"
#include "Keycodes.h"
#include "Collision.h"
#include "Camera.h"
#include <iostream>
#include <fstream>

class Game
{
public:
	Game();
	void InitCamera();
	int Run();

private:
	void KeyboardInputs(const float& dt);
	void PrintToFile();
	void Update();
	void Render();
	void LoadMap();

	Window window;
	Timer timer;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Cube>> bullets;
	//std::vector<std::unique_ptr<Projectile>> bullets;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Plane>> floortiles;
	std::unique_ptr<Plane> spawnpoint;

	Collision collider;

	bool bullet_fired = false;
};

