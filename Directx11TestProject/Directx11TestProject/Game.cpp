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

    wnd.getRenderer().SetCamera(camera.GetMatrix());

    /////////////////////////////////////////
    /// MOVE THIS OUT OF UPDATE YOU MANIAC //
    /////////////////////////////////////////
    //level.loadMap(Level::Map::ONE, wnd);
    std::fstream level_file;
    level_file.open("LevelMap1.txt");
    char wall = '#';
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
        if (level_file.get() == wall)
        {
            wnd.getRenderer().InitCube(angle, x * SPACING -5.0f, y * SPACING, z * SPACING);
            //wnd.getRenderer().DrawCube();
        }
        //else // Floor (UNCOMMENT THIS BACK IN WHEN LEVEL OPENING IS HANDLED IN CONSTRUCTOR)
        //{
        //    wnd.getRenderer().InitCube(angle, x * SPACING -5.0f, y * SPACING -SPACING, z * SPACING);
        //}
    }
    level_file.close();
    
    // TRANSLATION
    if (wnd.kbd.KeyIsPressed('W')) //FORWARDS TRANSLATION
    {
        camera.Translate({ 0.0f,0.0f,dt });
    }
    if (wnd.kbd.KeyIsPressed('S')) //BACKWARDS TRANSLATION
    {
        camera.Translate({ 0.0f,0.0f,-dt });
    }
    
    // ROTATION
    if (wnd.kbd.KeyIsPressed('A')) //LEFT ROTATION
    {
        camera.Rotate(-dt, 0.0f);
    }
    if (wnd.kbd.KeyIsPressed('D')) //RIGHT ROTATION
    {
        camera.Rotate(dt, 0.0f);
    }

    //wnd.getRenderer().InitCube(-timer.Peek(), -5.0f, 5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.getRenderer().InitCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 5.0f);
    wnd.getRenderer().EndFrame();
}