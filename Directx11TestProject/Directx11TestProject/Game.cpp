#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	window.getRenderer().SetProjectionMatrix(DirectX::XMMatrixPerspectiveRH(1.0F, 3.0F / 4.0F, 0.5F, 100.0F));
	LoadMap();
	InitCamera();
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

void Game::KeyboardInputs(float& dt)
{
	//if (dt > 2.0f)
	//{
	//	fire_bullet = false;
	//	// reset timer
	//}

	if (window.keyboard.KeyIsPressed(Keycodes::SPACE) /*&& !fire_bullet*/)
	{
		CreateBullet(dt);
		//fire_bullet = true;
	}

	if (window.keyboard.KeyIsPressed('M'))
	{
		PrintToFile();
	}
}

void Game::Update()
{
	auto dt = timer.Mark() * 1.0f;
	//auto clock = timer.TimeElapsed();
	camera->Update(window, dt);

	//timer.Peek();

	//if (timer.Peek() > 10)
	//{
	//	fire_bullet = false;
	//	// reset timer
	//}

	KeyboardInputs(dt);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		// Stop detecting collisons if bullets have been destroyed
		if (!bullets[i]->IsDestroyed())
		{
			bullets[i]->Update(dt);
		}

		// BULLET and ENEMY COLLISION
		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (collider.CollisionBox(bullets[i]->GetCube()->GetPos(), enemies[j]->GetPos()))
			{
				OutputDebugString("BULLET COLLISION WITH ENEMY DETECTED\n");
				bullets[i]->Destroy();
				enemies[j]->Destroy();
			}
		}

		// BULLET and WALL COLLISION
		for (size_t j = 0; j < cubes.size(); j++)
		{
			DirectX::XMFLOAT3 cube_pos { -cubes[j]->GetPos().x, cubes[j]->GetPos().y, -cubes[j]->GetPos().z };
			DirectX::XMFLOAT3 bullet_pos = { -bullets[i]->GetCube()->GetPos().x, bullets[i]->GetCube()->GetPos().y, -bullets[i]->GetCube()->GetPos().z };
			if (collider.CollisionBox(bullet_pos, cube_pos) /*&& !cubes[j]->IsDestroyed()*/)
			{
				OutputDebugString("BULLET COLLISION WITH WALL DETECTED\n");
				bullets[i]->Destroy();
				cubes[j]->Destroy();
			}
		}
	}

	/*if (fire_bullet)
	{*/
	//if (bullets[current_bullet-1] != NULL)
	//{
	//	bullets[current_bullet-1]->Update(dt);

	//	for (size_t i = 0; i < enemies.size(); i++)
	//	{
	//		if (collider.CollisionBox(bullets[current_bullet-1]->GetCube()->GetPos(), enemies[i]->GetPos()))
	//		{
	//			OutputDebugString("BULLET COLLISION WITH ENEMY DETECTED\n");
	//			bullets[current_bullet-1]->Destroy();
	//			enemies[i]->Destroy();
	//			//fire_bullet = false;
	//		}
	//	}
	//}
	/*}*/

	// ENEMY and PLAYER COLLISION
	for (size_t i = 0; i < enemies.size(); i++)
	{
		DirectX::XMFLOAT3 enemy_pos{ -enemies[i]->GetPos().x, enemies[i]->GetPos().y, -enemies[i]->GetPos().z };
		if (collider.CollisionBox(camera->GetPosition(), enemy_pos)) // adapt to suit plane size (atm only works properly with cubes)
		{
			OutputDebugString("ENEMY COLLISION DETECTED\n");
		}
	}

	// WALL COLLISION
	for (size_t i = 0; i < cubes.size(); i++)
	{
		DirectX::XMFLOAT3 cube_pos{ -cubes[i]->GetPos().x, cubes[i]->GetPos().y, -cubes[i]->GetPos().z };
		if (collider.CollisionBox(camera->GetPosition(), cube_pos))
		{
			OutputDebugString("WALL COLLISION DETECTED\n");
		}
	}

	// Update Enemy Rotation
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
		if (!cube->IsDestroyed())
		{
			cube->Render(window.getRenderer());
		}
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
	for (auto& bullet : bullets)
	{
		/*if (!bullet->IsDestroyed())
		{*/
			bullet->Render(window.getRenderer());
		/*}*/
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
			spawnpoint = std::make_unique<Plane>(window.getRenderer(), L"spawnpoint.jpg", DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, -0.98f, z * SPACING));
			break;
		}

		// Floor
		DirectX::XMFLOAT2 floor_size { 1.0, 1.0f };
		DirectX::XMFLOAT3 floor_pos  { x * SPACING, -1.0f, z * SPACING };
		floortiles.push_back(std::make_unique<Plane>(window.getRenderer(), L"greyfloor.jpg", floor_size, floor_pos));
	}
	level_file.close();
}

void Game::InitCamera()
{
	DirectX::XMFLOAT3 spawnpoint_pos{ spawnpoint->GetPos().x, 0.0f, spawnpoint->GetPos().z };
	camera = std::make_unique<Camera>(window.getRenderer());
	camera->SetView({ -spawnpoint_pos.x , spawnpoint_pos.y, -spawnpoint_pos.z }, DirectX::XMConvertToRadians(0));
}

void Game::PrintToFile()
{
	//float clock = timer.TimeElapsed();

	std::ofstream out("out.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt

	std::cout << "CAMERA \nX: [" << camera->GetPosition().x << "]\nY: [" << camera->GetPosition().y << "]\nZ: [" << camera->GetPosition().z << "]\n" << std::endl;
	std::cout << "ENEMY \nX: [" << enemies[3]->GetPos().x << "]\nY: [" << enemies[3]->GetPos().y << "]\nZ: [" << enemies[3]->GetPos().z << "]\n" << std::endl;
	//std::cout << "BULLET \nX: [" << bullets[0]->GetPos().x << "]\nY: [" << bullets[0]->GetPos().y << "]\nZ: [" << bullets[0]->GetPos().z << "]\n" << std::endl;

	//std::cout << "\nTime elapsed: " << clock << std::endl;
	std::cout << "Timer peek: " << timer.TimeElapsed() << std::endl;

	std::cout.rdbuf(coutbuf); //reset to standard output again
}

void Game::CreateBullet(float& dt)
{
	//timer.Peek();

	//if (timer.Peek() > 10)
	//{
	//	fire_bullet = false;
	//	// reset timer
	//}


	// if x amount of seconds passed, create new bullet

	DirectX::XMFLOAT3 bullet_size{ 0.10f, 0.10f, 0.10f };
	DirectX::XMFLOAT3 bullet_pos{ -camera->GetPosition().x + sin(camera->GetRotation()),
		                           camera->GetPosition().y - 0.25f,
		                          -camera->GetPosition().z - cos(camera->GetRotation()) };
	float bullet_rot = camera->GetRotation();
	bullets.push_back(std::make_unique<Projectile>(window.getRenderer(), L"bullet.jpg", bullet_size, bullet_pos, bullet_rot));
	current_bullet++;
}

