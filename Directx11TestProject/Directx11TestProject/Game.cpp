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
    wnd.Gfx().ClearBuffer(c, c, 1.0f); 
    wnd.Gfx().DrawTestTriangle(-timer.Peek(), 0.0f, 0.0f);
    wnd.Gfx().DrawTestTriangle(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
    wnd.Gfx().EndFrame();
}