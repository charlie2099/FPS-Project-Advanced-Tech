#include "Game.h"

Game::Game()
	:
	wnd(800, 600, "FPS Window")
{}

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
    /*const float t = timer.Peek();
    std::ostringstream oss;
    oss << "Time Elpased: " << std::setprecision(1) << std::fixed << t << "s";*/


    const float c = sin(timer.Peek()) / 2.0f + 0.5f;
    wnd.Gfx().ClearBuffer(0, 0, 0); 

    /// <CREDIT>
    /// Had problems with parsing a text file to render my cubes to form the layout of my level. 
    /// Andrei helped me solve this.
    /// </CREDIT>
    std::fstream level_file;
    level_file.open("Level.txt");
    char wall = '#';
    int row = 0;
    int column = 0;

    int row_len = 9;
    int column_len = 5;

    while (!level_file.eof())
    {
        row++;
        if (row == 10)
        {
            column++;
            row = 0;
        }
        if (level_file.get() == wall)
        {
            wnd.Gfx().DrawCube(0.0f, row * 2 - row_len, column * 2 - column_len, 5.0f);
        }
    }
    level_file.close();

    //wnd.Gfx().DrawCube(-timer.Peek(), -5.0f, 5.0f); // def: (0,0),(0,0)
    //wnd.Gfx().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
    wnd.Gfx().EndFrame();
}