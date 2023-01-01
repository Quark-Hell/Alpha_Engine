#include <iostream>
#include "Main.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"
#include "Physics.cpp"
#include "IO.cpp"
#include <Windows.h>
#include <thread>
#include <future>

Object obj;
Camera* camera = new Camera;


GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;


void GameFunction::Start() {
    std::string link = "\\Models\\Blender.fbx";

    Physics* phys = new Physics;
    Mesh* mesh = new Mesh;

    mesh->CreateMesh(link);

    obj.SetScale(1.3, 1.3,1.3);
    obj.AddModule(phys);
    obj.AddModule(mesh);

    Vector3 Postion{ 0,0,-5 };
    Vector3 Rotation(0, 30, 40);
    Vector3 Scale{ 0.8f,0.8f,0.8f };
    Vector3 Color{ 0,0,1 };

    Object* cube = Primitives::Sphere(Postion, Rotation, Scale, Color);

    Bind LeftMove{ std::vector<void(*)()>{LeftMoveCamera},  (sf::Event::EventType)- 1 , {EnumKeyStates::KeyHold}, {sf::Keyboard::A}};
    Bind RightMove{ std::vector<void(*)()>{RightMoveCamera},  (sf::Event::EventType)-1, {EnumKeyStates::KeyHold}, {sf::Keyboard::D} };
    Bind UpMove{ std::vector<void(*)()>{UpMoveCamera},  (sf::Event::EventType)-1, {EnumKeyStates::KeyHold}, {sf::Keyboard::W} };
    Bind DownMove{ std::vector<void(*)()>{DownMoveCamera},  (sf::Event::EventType)-1, {EnumKeyStates::KeyHold}, {sf::Keyboard::S} };

    Bind CameraRot{
    std::vector<void(*)()>{CameraRotate},
     (sf::Event::EventType)-1,
    {},
    {},
    {},
    {},
    MouseKeepMoved };

    Bind CloseGameFirstMethod{ std::vector<void(*)()>{World::CloseGame}, (sf::Event::EventType)-1, {EnumKeyStates::KeyReleased}, {sf::Keyboard::Escape} };
    Bind CloseGameSecondMethod{ std::vector<void(*)()>{World::CloseGame}, {sf::Event::EventType::Closed}, {}, {}, {EnumKeyStates::KeyReleased} ,{sf::Mouse::Left} };

    InpSys->InsertBind(LeftMove);
    InpSys->InsertBind(RightMove);
    InpSys->InsertBind(UpMove);
    InpSys->InsertBind(DownMove);
    InpSys->InsertBind(CameraRot);

    InpSys->InsertBind(CloseGameFirstMethod);
    InpSys->InsertBind(CloseGameSecondMethod);
}

void GameFunction::Update() {
    obj.SetPosition(0, 0, -3);
    obj.SetRotation(0, obj.GetRotation().Y + 1.5, 0);
}

void LeftMoveCamera() {
    Vector3 newPos = camera->GetPosition();
    Vector3 newRot = camera->GetRotation();

    newPos.X += 0.1;

    camera->SetCameraInfo(newPos, newRot);
}
void RightMoveCamera() {
    Vector3 newPos = camera->GetPosition();
    Vector3 newRot = camera->GetRotation();

    newPos.X -= 0.1;

    camera->SetCameraInfo(newPos, newRot);
}

void UpMoveCamera() {
    Vector3 newPos = camera->GetPosition();
    Vector3 newRot = camera->GetRotation();

    newPos.Z += 0.1;

    camera->SetCameraInfo(newPos, newRot);
}
void DownMoveCamera() {
    Vector3 newPos = camera->GetPosition();
    Vector3 newRot = camera->GetRotation();

    newPos.Z -= 0.1;

    camera->SetCameraInfo(newPos, newRot);
}

void CameraRotate() {
    float sensitive = 0.15;

    if (InpSys->GetMouseClass()->IsMouseChangePosition()) {

        Vector3 delta = InpSys->GetMouseClass()->GetMouseDelta();

        if (delta.GetMagnitude(delta) < 100) {
        Vector3 pos = camera->GetPosition();
        Vector3 rot = camera->GetRotation();

        rot.X += delta.Y * sensitive;
        rot.Y += delta.X * sensitive;

        camera->SetCameraInfo(pos, rot);
        }
    }
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, 1);
    

    Game->Start();
    render->StartRender(camera);
    InpSys->ScreenClass = render->GetScreenClass();
    
    while (!World::GetStateOfGame())
    {
        InpSys->IO_Events();
        Game->Update();
        render->RenderLoop(camera);   
    }
}
