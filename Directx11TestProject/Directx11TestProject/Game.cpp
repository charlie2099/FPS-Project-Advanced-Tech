#include "Game.h"

namespace dx = DirectX;

Game::Game()
    :
    wnd(1280, 720, "FPS Window")
{
    //wnd.getRenderer().initCube(angle, x * SPACING_X - (row_len + 1), y * SPACING_Y - column_len, z + (SPACING_Z * i));
    wnd.getRenderer().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f)); // 1.0f, 3.0f / 4.0f, 0.5f, 60.0f
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

    //wnd.getRenderer().SetCamera(dx::XMMatrixTranslation(0.0f, 0.0f, 0.0f) * dx::XMVector3Rotate(0.1f, 0.0f, 0.0f);
    wnd.getRenderer().SetCamera(camera.GetMatrix());

    ////////////////////////////////////
    /// MOVE OUT OF UPDATE YOU MANIAC //
    ////////////////////////////////////
    //level.loadMap(Level::Map::ONE, wnd);
    std::fstream level_file;
    level_file.open("LevelMap2.txt");
    char wall = '#';
    int row_len = 22; 
    int column_len = 16; 

    float angle = 0.0f;
    float x = 0.0f;
    float y = 15.5f; //5.5f
    float z = 0.0f; //6.0f

    const float SPACING_X = 1.9f;
    const float SPACING_Y = 1.9f;
    const float SPACING_Z = 1.9f;

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
                wnd.getRenderer().InitCube(angle, x * SPACING_X - (row_len + 1), y * SPACING_Y - column_len, z + (SPACING_Z * i));
                //wnd.getRenderer().DrawCube();
            }
        }
    }
    level_file.close();
    
    // TRANSLATION
    if (wnd.kbd.KeyIsPressed('W')) //FORWARDS
    {
        camera.Translate({ 0.0f,0.0f,dt });
    }
    if (wnd.kbd.KeyIsPressed('S')) //BACKWARDS
    {
        camera.Translate({ 0.0f,0.0f,-dt });
    }
    if (wnd.kbd.KeyIsPressed('R')) //UP
    {
        camera.Translate({ 0.0f,dt,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('F')) //DOWN
    {
        camera.Translate({ 0.0f,-dt,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('A')) //LEFT
    {
        camera.Translate({ -dt,0.0f,0.0f });
    }
    if (wnd.kbd.KeyIsPressed('D')) //RIGHT
    {
        camera.Translate({ dt,0.0f,0.0f });
    }

    // ROTATION
    if (wnd.kbd.KeyIsPressed('Z')) //UP
    {
        camera.Rotate(0.0f, -dt);
    }
    if (wnd.kbd.KeyIsPressed('C')) //DOWN
    {
        camera.Rotate(0.0f, dt);
    }
    if (wnd.kbd.KeyIsPressed('E')) //RIGHT
    {
        camera.Rotate(dt, 0.0f);
    }
    if (wnd.kbd.KeyIsPressed('Q')) //lEFT
    {
        camera.Rotate(-dt, 0.0f);
    }

    //wnd.getRenderer().DrawCube(-timer.Peek(), -5.0f, 5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.getRenderer().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 5.0f);
    wnd.getRenderer().EndFrame();
}