#include "Game.h"

namespace dx = DirectX;

Game::Game()
    :
    wnd(800, 600, "FPS Window")
{
    //camera.init();
    wnd.getRenderer().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
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
    //camera.update();

    const float c = sin(timer.Peek()) / 2.0f + 0.5f;
    wnd.getRenderer().ClearBuffer(0, 0, 0); 

    wnd.getRenderer().SetCamera(camera.GetMatrix());

    while (const auto e = wnd.kbd.ReadKey())
    {
        if (!e->IsPress())
        {
            continue;
        }
    }

    if (wnd.kbd.KeyIsPressed('W'))
    {
        camera.Translate({ 0.0f,0.0f,dt });
    }
    if (wnd.kbd.KeyIsPressed('A'))
    {
        camera.Translate({ -dt,0.0f,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('S'))
    {
        camera.Translate({ 0.0f,0.0f,-dt });
    }
    if (wnd.kbd.KeyIsPressed('D'))
    {
        camera.Translate({ dt,0.0f,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('R'))
    {
        camera.Translate({ 0.0f,dt,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('F'))
    {
        camera.Translate({ 0.0f,-dt,0.0f });
    }





    //level.loadMap(Level::Map::ONE, wnd);
    std::fstream level_file;
    level_file.open("LevelMap1.txt");
    char wall = '#';
    int row_len = 22; //8
    int column_len = 16; //6

    float angle = 0.0f;
    float x = 0.0f;
    float y = 15.5f; //5.5f
    float z = 19.0f; //6.0f

    const float SPACING_X = 2.0f;
    const float SPACING_Y = 2.0f;
    const float SPACING_Z = 2.0f;

    while (!level_file.eof())
    {
        x++;
        if (x == (row_len + 1))
        {
            y--;
            x = 0;
        }
        if (level_file.get() == wall)
        {
            for (int i = 0; i < 2; i++)
            {
                wnd.getRenderer().DrawCube(angle, x * SPACING_X - (row_len + 1), y * SPACING_Y - column_len, z + (SPACING_Z * i));
            }
        }
    }
    level_file.close();

    //wnd.getRenderer().DrawCube(-timer.Peek(), -5.0f, 5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.getRenderer().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 5.0f);
    wnd.getRenderer().EndFrame();
}