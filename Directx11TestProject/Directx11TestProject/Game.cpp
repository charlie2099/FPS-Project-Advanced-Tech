#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	window.getRenderer().SetProjectionMatrix(DirectX::XMMatrixPerspectiveRH(1.0F, 3.0F / 4.0F, 0.5F, 100.0F));
	LoadMap();
	InitCamera();

	DirectX::XMFLOAT3 bullet_size{ 0.10f, 0.10f, 0.10f };
	DirectX::XMFLOAT3 bullet_pos{ 0.0f, 0.0f, 0.0f };
	bullets.push_back(std::make_unique<Cube>(window.getRenderer(), L"bullet.jpg", bullet_size, bullet_pos));
	bullets[0]->SetPos({ -camera->GetPosition().x + sin(camera->GetRotation()), camera->GetPosition().y - 0.25f, -camera->GetPosition().z + cos(camera->GetRotation()) - 1.65f });
	bullets[0]->SetRotation(camera->GetRotation());
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
	if (window.keyboard.KeyIsPressed(Keycodes::SPACE) && !bullet_fired)
	{
		bullet_fired = true;


		/* TODO:
		* Instantiate bullet when SPACEBAR is pressed
		* Bullet fire rate, (set bullet_firing bool to false every 2 seconds)
		*/







		/*DirectX::XMFLOAT3 bullet_size{ 0.10f, 0.10f, 0.10f };
		DirectX::XMFLOAT3 bullet_pos{ 0.0f, 0.0f, 0.0f };
		bullets.push_back(std::make_unique<Cube>(window.getRenderer(), L"bullet.jpg", bullet_size, bullet_pos));
		bullets[0]->SetPos({ -camera->GetPosition().x + sin(camera->GetRotation()), camera->GetPosition().y - 0.25f, -camera->GetPosition().z + cos(camera->GetRotation()) });
		bullets[0]->SetRotation(camera->GetRotation());*/
	}

	if (window.keyboard.KeyIsPressed('M'))
	{
		PrintToFile();
	}
}

void Game::Update()
{
	auto dt = timer.Mark() * 1.0f;
	camera->Update(window, dt);
	KeyboardInputs(dt);


	if (!bullet_fired)
	{
		bullets[0]->SetPos({ -camera->GetPosition().x + sin(camera->GetRotation()),
			                  camera->GetPosition().y - 0.25f, 
			                 -camera->GetPosition().z - cos(camera->GetRotation()) });
		bullets[0]->SetRotation(camera->GetRotation());
	}


	// ENEMY and BULLET COLLISION
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullet_fired)
		{
			//bullets[i]->SetPos({ bullets[i]->GetPos().x, bullets[i]->GetPos().y,  bullets[i]->GetPos().z - 5.0f * dt });

			const float speed = 5.0f;
			bullets[i]->SetPos({ bullets[i]->GetPos().x + sin(bullets[i]->GetRot()) * speed * dt, 
				                 bullets[i]->GetPos().y,
								 bullets[i]->GetPos().z - cos(bullets[i]->GetRot()) * speed * dt });
			bullets[0]->SetRotation(camera->GetRotation());
		}

		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (collider.CollisionBox(bullets[i]->GetPos(), enemies[j]->GetPos())) // adapt to suit plane size (atm only works properly with cubes)
			{
				OutputDebugString("BULLET COLLISION WITH ENEMY DETECTED\n");
				enemies[j]->Destroy();
				bullets[i]->Destroy();
				//bullets.pop_back();
				//bullet_move = false;
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
	for (auto& bullet : bullets)
	{
		if (bullet->IsAlive()) // refactor
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
	std::ofstream out("out.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt

	std::cout << "CAMERA \nX: [" << camera->GetPosition().x << "]\nY: [" << camera->GetPosition().y << "]\nZ: [" << camera->GetPosition().z << "]\n" << std::endl;
	std::cout << "ENEMY \nX: [" << enemies[3]->GetPos().x << "]\nY: [" << enemies[3]->GetPos().y << "]\nZ: [" << enemies[3]->GetPos().z << "]\n" << std::endl;
	std::cout << "BULLET \nX: [" << bullets[0]->GetPos().x << "]\nY: [" << bullets[0]->GetPos().y << "]\nZ: [" << bullets[0]->GetPos().z << "]\n" << std::endl;

	std::cout.rdbuf(coutbuf); //reset to standard output again
}

