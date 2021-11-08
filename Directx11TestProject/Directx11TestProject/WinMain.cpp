#include "Window.h"
#include <iostream>
#include <d3d11.h>
#include "Game.h"

#pragma comment (lib, "d3d11.lib")

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    return Game{}.Run();
}
