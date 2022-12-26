#include <iostream>
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"
#include <Windows.h>

class GameClass
{
public:
    void Game() {

    }
};

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, 0);

    //GameClass game;
    //game.Game();
    Render render;
    render.RenderLoop();
}
