#pragma once
#include "Window.h"
#include "Time.h"
#include "Cube.h"
#include "Enemy.h"
#include "Plane.h"
#include "Constants.h"
#include "Colours.h"
#include "Keycodes.h"
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
	Time time;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Cube>> walls;
	std::vector<std::unique_ptr<Projectile>> bullets;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Plane>> floortiles;
	std::unique_ptr<Plane> spawnpoint;
	std::unique_ptr<Cube> winscreen;

	bool isComplete       = false;
	float time_passed     = 0.0f;
	float fire_rate       = 0.5f;
	size_t current_bullet = 0;
};

