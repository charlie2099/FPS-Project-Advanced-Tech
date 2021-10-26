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

    wnd.Gfx().ClearBuffer(0, 0, 0); 
    wnd.Gfx().DrawTestTriangle(0.0f); 
    wnd.Gfx().EndFrame();
}