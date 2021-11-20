#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	LoadMap();

	// Camera origin
	//DirectX::XMFLOAT3 camera_pos { spawnpoint->GetPos().x, spawnpoint->GetPos().y, spawnpoint->GetPos().z };


	camera = std::make_unique<Camera>(window.getRenderer());
	camera->SetView({ -5.0f, 0.0f, -25.0f });


	cubes[0]->SetPos({ 0,0,0 });

	// Spawn one bullet
	for (int i = 0; i < 1; i++)
	{
		DirectX::XMFLOAT3 bullet_size{5.0f, 5.0f, 5.0f};
		DirectX::XMFLOAT3 bullet_pos{ 5.0f, 10.0f, 0.0f };
		bullets.push_back(std::make_unique<Cube>(window.getRenderer(), L"Palpatine.jpg", bullet_size, bullet_pos));
	}
}

int Game::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}

		Update();
		Render();
	}
}

void Game::KeyboardInputs(const float& dt)
{
	//camera->Update();

	auto speed = 2.0f;
	if (window.keyboard.KeyIsPressed(Keycodes::W)) //FORWARDS TRANSLATION
	{
		camera->SetPosition({ 0.0f, 0.0f, speed * dt });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::S)) //BACKWARDS TRANSLATION
	{
		camera->SetPosition({ 0.0f, 0.0f, -speed * dt });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::W) && window.keyboard.KeyIsPressed(Keycodes::SHIFT)) //SPRINT
	{
		camera->SetPosition({ 0, 0, speed * 1.15f * dt });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::A)) //LEFT ROTATION
	{
		camera->SetRotation(-speed * dt);
	}
	if (window.keyboard.KeyIsPressed(Keycodes::D)) //RIGHT ROTATION
	{
		camera->SetRotation(speed * dt);
	}

	const int SPACEBAR = 32;
	if (window.keyboard.KeyIsPressed(Keycodes::SPACE))
	{
		bullet_move = true;
	}

	if (window.keyboard.KeyIsPressed('M'))
	{
		//window.getRenderer().GetViewPos();

		// PROBLEM: View pos returns correct position, but GetPosition() doesn't?! Gives values like 0.001 
		camera->GetPosition();
	}
}

void Game::Update()
{
	const auto dt = timer.Mark() * 1.0f;
	KeyboardInputs(dt);

	if(bullet_move)
	{
		bullets[0]->SetPos({ bullets[0]->GetPos().x + 2 * dt, bullets[0]->GetPos().y, bullets[0]->GetPos().z });
	}

	for (size_t i = 0; i < cubes.size(); i++)
	{
		if (collider.CollisionBox(camera->GetPosition(), { -5.0f, 0.0f, -13.0f } /*cubes[i]->GetPos()*/))
		{
			OutputDebugString("COLLISION DETECTED\n");
		}
	}
}

void Game::Render()
{
	window.getRenderer().ClearBuffer(Colours::BLUE_PURPLE); 

	for (auto& cube : cubes)
	{
		cube->Render(window.getRenderer());
	}
	for (auto& enemy : enemies)
	{
		enemy->Render(window.getRenderer());
	}
	for (auto& tiles : floortiles)
	{
		tiles->Render(window.getRenderer());
	}
	for (auto& bullet : bullets)
	{
		bullet->Render(window.getRenderer());
	}
	spawnpoint->Render(window.getRenderer());

	window.getRenderer().EndFrame();
}

void Game::LoadMap()
{
	std::fstream level_file;
	level_file.open("Level_Map_1.txt");
	float angle = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	const float SPACING = 1.9f;

	while (!level_file.eof())
	{
		x++;
		if (level_file.peek() == '\n')
		{
			z++;
			x = 0;
		}

		char level_char = level_file.get();
		switch (level_char)
		{
		case '#': // Wall
			DirectX::XMFLOAT3 cube_size { 1.0, 1.0f, 1.0f };
			DirectX::XMFLOAT3 cube_pos  { x * SPACING, 0.0f, z * SPACING };
			cubes.push_back(std::make_unique<Cube>(window.getRenderer(), cube_size, cube_pos));
			break;
		case 'E': // Enemy
			DirectX::XMFLOAT2 enemy_size { 0.5f, 1.0f };
			DirectX::XMFLOAT3 enemy_pos  { x * SPACING, -0.25f, z * SPACING };
			enemies.push_back(std::make_unique<Enemy>(window.getRenderer(), enemy_size, enemy_pos));
			break;
		case 'S':
			spawnpoint = std::make_unique<Cube>(window.getRenderer(), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, -1.9f, z * SPACING));
			break;
		}

		// Floor
		DirectX::XMFLOAT2 floor_size { 1.0, 1.0f };
		DirectX::XMFLOAT3 floor_pos  { x * SPACING, -1.0f, z * SPACING };
		floortiles.push_back(std::make_unique<Plane>(window.getRenderer(), floor_size, floor_pos));
	}
	level_file.close();
}

