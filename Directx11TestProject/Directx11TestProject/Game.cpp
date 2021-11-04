#include "Game.h"

Game::Game()
    :
    wnd(800, 600, "FPS Window")
{
    //camera.init();
}

int Game::Go()
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
    //camera.update();

    const float c = sin(timer.Peek()) / 2.0f + 0.5f;
    wnd.getRenderer().ClearBuffer(0, 0, 0); 

    //level.loadMap(Level::Map::ONE, wnd);

    /// <CREDIT>
    /// Struggled with parsing a text file to to construct the level map from cubes. 
    /// Andrei helped me configure it properly.
    /// </CREDIT>
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

    //wnd.Gfx().DrawCube(-timer.Peek(), -5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.Gfx().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
    wnd.getRenderer().EndFrame();
}