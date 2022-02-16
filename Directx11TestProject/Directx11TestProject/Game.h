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
#include "Projectile.h"
#include <iostream>
#include <fstream>

class Game
{
public:
	Game();
	void InitCamera();
	int Run();

private:
	void KeyboardInputs(float& dt);
	void CreateBullet(float& dt);
	void PrintToFile();
	void Update();
	void Render();
	void LoadMap();

	Window window;
	Timer timer;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Projectile>> bullets;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Plane>> floortiles;
	std::unique_ptr<Plane> spawnpoint;

	Collision collider;

	//bool fire_bullet = false;
	size_t fire_rate = 2;
	size_t current_bullet = 0;
};

