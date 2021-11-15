#include "Game.h"

namespace dx = DirectX;

Game::Game()
    :
    window(1280, 720, "FPS Window")
{
    //cube = std::make_unique<Cube>(window.getRenderer(), 0, -2.0f, -1.5f, 3);
    window.getRenderer().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f)); // 1.0f, 3.0f / 4.0f, 0.5f, 60.0f
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

  /*TODO
   * Sat: REFACTORING + TEXTURING
   * Sun: COLLISIONS
   * Mon: BILLBOARD ENEMIES + SHOOTING
   * Tues: REPORT
   * Weds: REPORT
   */

void Game::Update()
{
    const auto dt = timer.Mark() * speed_factor;
    const float c = sin(timer.Peek()) / 2.0f + 0.5f;
    window.getRenderer().ClearBuffer(0, 0, 0); 
    window.getRenderer().SetCamera(camera.GetMatrix());

    //cube->Render(window.getRenderer());
    //cube = std::make_unique<Cube>(window.getRenderer(), 0, -2.0f, -1.5f, 3);
    //cube = std::make_unique<Cube>(window.getRenderer(), timer.Peek(), window.mouse.GetPosX() / 400.0f - 1.0f, -window.mouse.GetPosY() / 300.0f + 1.0f, 5.0f);

    /////////////////////////////////////////
    /// MOVE THIS OUT OF UPDATE YOU MANIAC //
    /////////////////////////////////////////
    //level.loadMap(Level::Map::ONE, window);
    std::fstream level_file;
    level_file.open("LevelMap1.txt");
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
            level_block = std::make_unique<Cube>(window.getRenderer(), angle, x * SPACING - 5.0f, y * SPACING, z * SPACING);
            break;
        case 'E': // Enemy
            cube = std::make_unique<Cube>(window.getRenderer(), angle, x * SPACING - 5.0f, y * SPACING, z * SPACING);
            break;
        case '-': // Floor
            //level_block = std::make_unique<Cube>(window.getRenderer(), angle, x * SPACING - 5.0f, y * SPACING - SPACING, z * SPACING);
            break;
        }
    }
    level_file.close(); 

    plane = std::make_unique<Plane>(window.getRenderer(), dx::XMFLOAT3(6, 1, 3));
    
    KeyInputs(dt);

    window.getRenderer().EndFrame();
}

void Game::KeyInputs(const float& dt)
{
    // TRANSLATION
    if (window.kbd.KeyIsPressed('W')) //FORWARDS TRANSLATION
    {
        camera.Translate({ 0.0f,0.0f,dt });
    }
    if (window.kbd.KeyIsPressed('S')) //BACKWARDS TRANSLATION
    {
        camera.Translate({ 0.0f,0.0f,-dt });
    }

    // ROTATION
    if (window.kbd.KeyIsPressed('A')) //LEFT ROTATION
    {
        camera.Rotate(-dt, 0.0f);
    }
    if (window.kbd.KeyIsPressed('D')) //RIGHT ROTATION
    {
        camera.Rotate(dt, 0.0f);
    }
}
