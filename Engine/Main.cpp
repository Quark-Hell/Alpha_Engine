#include <iostream>
#include "Main.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"

#include "GameModels.cpp"

#include "Physics.cpp"
#include "Mesh.cpp"
#include "Camera.cpp"

#include "IO.cpp"
#include <Windows.h>
#include <thread>
#include <future>

Object obj;

Object Player;
Camera* camera = new Camera;


GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;


void GameFunction::Start() {
    std::string link = "\\Models\\Blender.fbx";

    Player.AddModule(camera);

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
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector;

    UpVector.X = sin((Player.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sin((Player.GetRotation().Y) * 3.14159 / 180);

    newPos += UpVector * 0.1;

    Player.SetPosition(newPos);
}
void RightMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector;

    UpVector.X = sin((Player.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sin((Player.GetRotation().Y) * 3.14159 / 180);

    newPos += UpVector * (-0.1);

    Player.SetPosition(newPos);
}

void UpMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector{0,0,0};

    UpVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    UpVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    UpVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += UpVector * 0.1;

    Player.SetPosition(newPos);
}
void DownMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector{0,0,0};

    UpVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    UpVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    UpVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += UpVector * (-0.1);

    Player.SetPosition(newPos);
}

void CameraRotate() {
    float sensitive = 0.15;

    if (InpSys->GetMouseClass()->IsMouseChangePosition()) {

        Vector3 delta = InpSys->GetMouseClass()->GetMouseDelta();


        if (delta.GetMagnitude() < 100) {
        Vector3 newRot = Player.GetRotation();

        Vector3 test;
        test.X = cos((Player.GetRotation().X) * 3.14159 / 180);
        test.Y = sin((Player.GetRotation().Y) * 3.14159 / 180);


        std::cout << test.X << std::endl;
        std::cout << test.Y << std::endl;
        std::cout << std::endl;

        newRot.X += delta.Y * sensitive;
        newRot.Y += delta.X * sensitive;

        Player.SetRotation(newRot);
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

    camera->GetDirectionOfView();
    
    while (!World::GetStateOfGame())
    {
        InpSys->IO_Events();
        Game->Update();
        render->RenderLoop(camera);   
        //std::cout << camera->GetDirectionOfView().X << std::endl;
        //std::cout << camera->GetDirectionOfView().Y << std::endl;
        //std::cout << camera->GetDirectionOfView().Z << std::endl;

        //std::cout << std::endl;
    }
}
