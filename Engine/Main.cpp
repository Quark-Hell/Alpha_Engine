#include <iostream>
#include "Main.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"
#include <Windows.h>

Object obj;

void GameFunction::Start() {
    std::string link = "\\Models\\text.fbx";

    Physics* phys = new Physics;
    Mesh* mesh = new Mesh;

    mesh->CreateMesh(link);

    obj.AddModule(phys);
    obj.AddModule(mesh);

    Vector3 Postion{ 0,0,-5 };
    Vector3 Rotation(0, 30, 40);
    Vector3 Scale{ 1,1,1 };
    Vector3 Color{ 0,0,1 };

    Object* cube = Primitives::Sphere(Postion, Rotation, Scale, Color);
}

void GameFunction::Update() {
    obj.SetPosition(0, 0, -3);
    obj.SetRotation(obj.GetRotation().X + 1, obj.GetRotation().Y + 1, 0);
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, 0);

    GameFunction* Game = new GameFunction;
    Render* render = new Render;

    Game->Start();
    render->StartRender();


    while (true)
    {
        Game->Update();
        render->RenderLoop();


    }
}
