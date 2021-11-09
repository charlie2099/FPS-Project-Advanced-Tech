#include "Game.h"
#include "Cube.h"
#include <memory>

namespace dx = DirectX;

Game::Game()
    :
    wnd(800, 600, "FPS Window")
{
    //camera.init();
    //wnd.getRenderer().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f)); // 1.0f, 3.0f / 4.0f, 0.5f, 60.0f

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
    for (auto i = 0; i < 80; i++)
    {
        cubes.push_back(std::make_unique<Cube>(
            wnd.getRenderer(), rng, adist,
            ddist, odist, rdist
            ));
    }
    wnd.getRenderer().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 60.0f));
}

int Game::Run()
{
    // Message loop
    while (true)
    {
        // Process all pending messages
        if (const auto ecode = Window::ProcessMessages())
        {
            return *ecode; 
        }
        Update(); 
    }
}

void Game::Update()
{
    const auto dt = timer.Mark() * speed_factor;
    const float c = sin(timer.Peek()) / 2.0f + 0.5f;
    wnd.getRenderer().ClearBuffer(0, 0, 0); 

    for (auto& c : cubes)
    {
        c->Update(dt);
        c->Draw(wnd.getRenderer());
    }

    //level.loadMap(Level::Map::ONE, wnd);
    //std::fstream level_file;
    //level_file.open("LevelMap1.txt");
    //char wall = '#';
    //int row_len = 22; //8
    //int column_len = 16; //6

    //float angle = 0.0f;
    //float x = 0.0f;
    //float y = 15.5f; //5.5f
    //float z = 19.0f; //6.0f

    //const float SPACING_X = 2.0f;
    //const float SPACING_Y = 2.0f;
    //const float SPACING_Z = 2.0f;

    //while (!level_file.eof())
    //{
    //    x++;
    //    if (x == (row_len + 1))
    //    {
    //        y--;
    //        x = 0;
    //    }
    //    if (level_file.get() == wall)
    //    {
    //        for (int i = 0; i < 2; i++)
    //        {
    //            wnd.getRenderer().DrawCube(angle, x * SPACING_X - (row_len + 1), y * SPACING_Y - column_len, z + (SPACING_Z * i));
    //        }
    //    }
    //}
    //level_file.close();

    //wnd.getRenderer().DrawCube(-timer.Peek(), -5.0f, 5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.getRenderer().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 5.0f);
    wnd.getRenderer().EndFrame();
}