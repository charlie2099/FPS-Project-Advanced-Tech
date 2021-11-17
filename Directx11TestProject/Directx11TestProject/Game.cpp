#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	LoadMap();

	// Camera origin
	//DirectX::XMFLOAT3 camera_pos { spawnpoint->GetPos().x, spawnpoint->GetPos().y, spawnpoint->GetPos().z };

	window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(-5,0,-5));

	// Spawn one bullet
	for (int i = 0; i < 1; i++)
	{
		DirectX::XMFLOAT3 bullet_size{ 0.5f, 0.5f, 0.5f };
		DirectX::XMFLOAT3 bullet_pos{ 4.0, 0.10f, 15.0f };
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
	}
}

void Game::KeyboardInputs(const float& dt)
{
	if (window.keyboard.KeyIsPressed('W')) //FORWARDS TRANSLATION
	{
		//camera.Translate({ 0.0f,0.0f,dt });
		float translation = 2.0f;
		window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f * dt * 2.0f, 0.0f, translation * dt * 2.0f)) * window.getRenderer().GetCBufferData().view;
	}
	if (window.keyboard.KeyIsPressed('S')) //BACKWARDS TRANSLATION																	
	{
		//camera.Translate({ 0.0f,0.0f,-dt });																						
		float translation = -2.0f;
		window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f * dt * 2.0f, 0.0f, translation * dt * 2.0f)) * window.getRenderer().GetCBufferData().view;
	}

	if (window.keyboard.KeyIsPressed('A')) //LEFT ROTATION
	{
		//camera.Rotate(-dt, 0.0f);
		float rotation = -2.0f;
		window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(rotation * dt)) * window.getRenderer().GetCBufferData().view;
	}
	if (window.keyboard.KeyIsPressed('D')) //RIGHT ROTATION
	{
		//camera.Rotate(dt, 0.0f);
		float rotation = 2.0f;
		window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(rotation * dt)) * window.getRenderer().GetCBufferData().view;
	}

	const int SPACEBAR = 32;
	if (window.keyboard.KeyIsPressed(SPACEBAR))
	{
		bullet_move = true;
	}

	//if (window.keyboard.KeyIsPressed('M'))
	//{
	//	// Set 'camera' position
	//	window.getRenderer().GetCBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f, 0.0F, 0.0f));
	//}
}

void Game::Update()
{
	const auto dt = timer.Mark() * 1.0f;
	KeyboardInputs(dt);

	if(bullet_move)
	{
		bullets[0]->SetPos({ bullets[0]->GetPos().x + 2 * dt, bullets[0]->GetPos().y, bullets[0]->GetPos().z });
	}

	Render();
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

