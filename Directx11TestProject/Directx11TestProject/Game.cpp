#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	LoadMap();

	// Camera origin
	DirectX::XMFLOAT3 spawnpoint_pos { spawnpoint->GetPos().x, 0.0f, spawnpoint->GetPos().z };
	camera = std::make_unique<Camera>(window.getRenderer());
	camera->SetView({ -spawnpoint_pos.x , spawnpoint_pos.y, -spawnpoint_pos.z }, DirectX::XMConvertToRadians(0));

	// Spawn palp cube
	for (int i = 0; i < 1; i++)
	{
		DirectX::XMFLOAT3 bullet_size{5.0f, 5.0f, 5.0f};
		DirectX::XMFLOAT3 bullet_pos { 5.0f, 10.0f, 0.0f };
		palp_cube.push_back(std::make_unique<Cube>(window.getRenderer(), L"Palpatine.jpg", bullet_size, bullet_pos));
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
	const int SPACEBAR = 32;
	if (window.keyboard.KeyIsPressed(Keycodes::SPACE) && !bullet_move)
	{
		bullet_move = true;
		DirectX::XMFLOAT3 bullet_size{ 0.15f, 0.15f, 0.15f };
		DirectX::XMFLOAT3 bullet_pos{ -camera->GetPosition().x, camera->GetPosition().y - 0.25f, -camera->GetPosition().z - 0.65f };
		bullets.push_back(std::make_unique<Cube>(window.getRenderer(), L"Palpatine.jpg", bullet_size, bullet_pos));
	}

	if (window.keyboard.KeyIsPressed('M'))
	{
		std::ofstream out("out.txt");
		coutbuf = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

		std::cout << "CAMERA \nX: [" << camera->GetPosition().x << "]\nY: [" << camera->GetPosition().y << "]\nZ: [" << camera->GetPosition().z << "]\n" << std::endl;

		std::cout << "ENEMY \nX: [" << enemies[3]->GetPos().x << "]\nY: [" << enemies[3]->GetPos().y << "]\nZ: [" << enemies[3]->GetPos().z << "]\n" << std::endl;

		//std::cout << "BULLET \nX: [" << bullets[0]->GetPos().x << "]\nY: [" << bullets[0]->GetPos().y << "]\nZ: [" << bullets[0]->GetPos().z << "]\n" << std::endl;

		std::cout.rdbuf(coutbuf); //reset to standard output again
	}
}

void Game::Update()
{
	const auto dt = timer.Mark() * 1.0f;
	camera->Update(window, dt);
	KeyboardInputs(dt);

	// ENEMY and BULLET COLLISION
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullet_move)
		{
			bullets[i]->SetPos({ bullets[i]->GetPos().x, bullets[i]->GetPos().y,  bullets[i]->GetPos().z - 1 * dt });
		}

		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (collider.CollisionBox(bullets[i]->GetPos(), enemies[j]->GetPos())) // adapt to suit plane size (atm only works properly with cubes)
			{
				OutputDebugString("BULLET COLLISION WITH ENEMY DETECTED\n");
				enemies[j]->Destroy();
				bullets[i]->Destroy();
				//bullets.pop_back();
				//bullets[i]->Destroy();
				//bullet_move = false;
				// enemies[i]->Destroy()   bool than triggers whether enemy is drawn or not
				//camera->SetView({ camera->GetPosition().x - 5, 0, camera->GetPosition().z - 5 });
			}
		}
	}

	// ENEMY and PLAYER COLLISION
	for (size_t i = 0; i < enemies.size(); i++)
	{
		DirectX::XMFLOAT3 enemy_pos{ -enemies[i]->GetPos().x, enemies[i]->GetPos().y, -enemies[i]->GetPos().z };
		if (collider.CollisionBox(camera->GetPosition(), enemy_pos)) // adapt to suit plane size (atm only works properly with cubes)
		{
			OutputDebugString("ENEMY COLLISION DETECTED\n");
			// enemies[i]->Destroy()   bool than triggers whether enemy is drawn or not
			//camera->SetView({ camera->GetPosition().x - 5, 0, camera->GetPosition().z - 5 });
		}
	}

	// WALL COLLISION
	for (size_t i = 0; i < cubes.size(); i++)
	{
		DirectX::XMFLOAT3 cube_pos{ -cubes[i]->GetPos().x, cubes[i]->GetPos().y, -cubes[i]->GetPos().z };
		if (collider.CollisionBox(camera->GetPosition(), cube_pos))
		{
			OutputDebugString("WALL COLLISION DETECTED\n");
			//camera->SetView({ camera->GetPosition().x - 5, 0, camera->GetPosition().z - 5 });
		}
	}

	for (auto& enemy : enemies)
	{
		enemy->SetRotation(camera->GetRotation());
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
		if (enemy->IsAlive())
		{
			enemy->Render(window.getRenderer());
		}
	}
	for (auto& tiles : floortiles)
	{
		tiles->Render(window.getRenderer());
	}
	for (auto& palp : palp_cube)
	{
		palp->Render(window.getRenderer());
	}
	for (auto& bullet : bullets)
	{
		if (bullet->IsAlive())
		{
			bullet->Render(window.getRenderer());
		}
	}
	spawnpoint->Render(window.getRenderer());

	window.getRenderer().EndFrame();
}

void Game::LoadMap()
{
	std::fstream level_file;
	level_file.open("Level_Map_3.txt");
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
			enemies.push_back(std::make_unique<Enemy>(window.getRenderer(), enemy_size, enemy_pos/*, 10.0f*/));
			break;
		case 'S':
			spawnpoint = std::make_unique<Cube>(window.getRenderer(), L"Palpatine.jpg", DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, -1.99f, z * SPACING));
			break;
		}

		// Floor
		DirectX::XMFLOAT2 floor_size { 1.0, 1.0f };
		DirectX::XMFLOAT3 floor_pos  { x * SPACING, -1.0f, z * SPACING };
		floortiles.push_back(std::make_unique<Plane>(window.getRenderer(), floor_size, floor_pos));
	}
	level_file.close();
}

