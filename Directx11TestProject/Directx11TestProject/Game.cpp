#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	LoadMap();

	// Camera origin
	DirectX::XMFLOAT3 spawnpoint_pos { spawnpoint->GetPos().x, 0.0f, spawnpoint->GetPos().z };
	camera = std::make_unique<Camera>(window.getRenderer());
	camera->SetView({ -spawnpoint_pos.x , spawnpoint_pos.y, -spawnpoint_pos.z }, DirectX::XMConvertToRadians(0));

	// Spawn one bullet
	for (int i = 0; i < 1; i++)
	{
		DirectX::XMFLOAT3 bullet_size{5.0f, 5.0f, 5.0f};
		DirectX::XMFLOAT3 bullet_pos{ 5.0f, 10.0f, 0.0f };
		bullets.push_back(std::make_unique<Cube>(window.getRenderer(), L"Palpatine.jpg", bullet_size, bullet_pos));
	}

	//enemies[3]->SetPos({ spawnpoint_pos });
	//enemies[3]->SetRotation(0);

	//std::ofstream out("out.txt");
	//coutbuf = std::cout.rdbuf(); //save old buf
	//std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	//std::cout << "X: [" << camera->GetPosition().x << "]\nY: [" << camera->GetPosition().y << "]\nZ: [" << camera->GetPosition().z << "]" << std::endl;
	//camera->SetPosition({ -spawnpoint_pos.x, spawnpoint_pos.y, -spawnpoint_pos.z });
	//camera->SetPosition(camera->GetPosition());

	//std::cout.rdbuf(coutbuf); //reset to standard output again
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
	camera->Update(window, dt);
	//auto speed = 2.0f;
	//if (window.keyboard.KeyIsPressed(Keycodes::W)) //FORWARDS TRANSLATION
	//{
	//	camera->Translate({ 0.0f, 0.0f, speed * dt });
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::S)) //BACKWARDS TRANSLATION
	//{
	//	camera->Translate({ 0.0f, 0.0f, -speed * dt });
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::W) && window.keyboard.KeyIsPressed(Keycodes::SHIFT)) //SPRINT
	//{
	//	camera->Translate({ 0, 0, speed * 1.15f * dt });
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::A)) //LEFT ROTATION
	//{
	//	camera->Rotate(-speed * dt);
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::D)) //RIGHT ROTATION
	//{
	//	camera->Rotate(speed * dt);
	//}

	const int SPACEBAR = 32;
	if (window.keyboard.KeyIsPressed(Keycodes::SPACE))
	{
		bullet_move = true;
	}

	if (window.keyboard.KeyIsPressed('M'))
	{
		std::ofstream out("out.txt");
		coutbuf = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

		// PROBLEM: View pos returns correct position, but GetPosition() doesn't?! Gives values like 0.001 
		std::cout << "CAMERA (X: [" << camera->GetPosition().x << "]\nY: [" << camera->GetPosition().y << "]\nZ: [" << camera->GetPosition().z << "])" << std::endl;

		std::cout << "CUBES (X: [" << cubes[3]->GetPos().x << "]\nY: [" << cubes[3]->GetPos().y << "]\nZ: [" << cubes[3]->GetPos().z << "])" << std::endl;

		std::cout.rdbuf(coutbuf); //reset to standard output again
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
		DirectX::XMFLOAT3 cube_pos{ -cubes[i]->GetPos().x, cubes[i]->GetPos().y, -cubes[i]->GetPos().z };
		if (collider.CollisionBox(camera->GetPosition(), cube_pos)) // -7.6f, 0.0f, -2.02f
		{
			OutputDebugString("COLLISION DETECTED\n");
			/* TODO
			 * Collision Response
		     */
		}
	}

	/*for (auto& enemy : enemies)
	{
		enemy->SetRotation(camera->GetRotation());
	}*/
	//enemies[3]->SetRotation(10);
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

