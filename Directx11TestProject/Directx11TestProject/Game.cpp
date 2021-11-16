#include "Game.h"

Game::Game() : window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "FPS Window")
{
	LoadMap();
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

void Game::Update()
{
	const auto dt = timer.Mark() * 1.0f;

	KeyboardInputs(dt);
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
	for (auto& plane : planes)
	{
		plane->Render(window.getRenderer());
	}

	window.getRenderer().EndFrame();
}

void Game::LoadMap()
{
	std::fstream level_file;
	level_file.open("Level_Map_1.txt");
	float angle = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 12.0f;
	const float SPACING = 1.9f;

	while (!level_file.eof())
	{
		x++;
		if (level_file.peek() == '\n')
		{
			z--;
			x = 0;
		}

		char level_char = level_file.get();
		switch (level_char)
		{
		case '#': // Wall
			cubes.push_back(std::make_unique<Cube>(window.getRenderer(), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, 0.0f, z * SPACING)));
			break;
		case 'E': // Enemy
			enemies.push_back(std::make_unique<Enemy>(window.getRenderer(), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, 0.0f, z * SPACING)));
			break;
		case 'S':
			// Spawn block
			planes.push_back(std::make_unique<Plane>(window.getRenderer(), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, -1.0f, z * SPACING)));
			// get position of the last plane that got pushed to the vector. Use to determine where camera should be positioned.

			// Set 'camera' position
			//window.getRenderer().constantBufferData.view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f, 0.0F, 0.0f));
			break;
		}

		// Floor
		planes.push_back(std::make_unique<Plane>(window.getRenderer(), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(x * SPACING, -1.0f, z * SPACING)));
	}
	level_file.close();
}

void Game::KeyboardInputs(const float& dt)
{
	// TRANSLATION
	if (window.keyboard.KeyIsPressed('W')) //FORWARDS TRANSLATION
	{
		//camera.Translate({ 0.0f,0.0f,dt });
		float translation = 2.0f;
		window.getRenderer().GetConstantBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f * dt * 2.0f, 0.0f, translation * dt * 2.0f)) * window.getRenderer().GetConstantBufferData().view;
	}
	if (window.keyboard.KeyIsPressed('S')) //BACKWARDS TRANSLATION																	
	{
		//camera.Translate({ 0.0f,0.0f,-dt });																						
		float translation = -2.0f;
		window.getRenderer().GetConstantBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0f * dt * 2.0f, 0.0f, translation * dt * 2.0f)) * window.getRenderer().GetConstantBufferData().view;
	}

	// ROTATION
	if (window.keyboard.KeyIsPressed('A')) //LEFT ROTATION
	{
		//camera.Rotate(-dt, 0.0f);
		float rotation = -2.0f;
		window.getRenderer().GetConstantBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(rotation * dt)) * window.getRenderer().GetConstantBufferData().view;
	}
	if (window.keyboard.KeyIsPressed('D')) //RIGHT ROTATION
	{
		//camera.Rotate(dt, 0.0f);
		float rotation = 2.0f;
		window.getRenderer().GetConstantBufferData().view = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(rotation * dt)) * window.getRenderer().GetConstantBufferData().view;
	}
}
