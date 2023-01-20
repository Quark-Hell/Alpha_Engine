#include <iostream>
#include "Main.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"

#include "GameModels.cpp"

#include "Physics.cpp"
#include "Mesh.cpp"
#include "Camera.cpp"
#include "Collision.cpp"

#include "Binds.cpp"

#include <ctime>

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
    Collision* collision = new Collision;

    mesh->CreateMesh(link);
    collision->CreateCollision(link);

    obj.SetScale(0.5, 0.5, 0.5);

    obj.AddModule(phys);
    //obj.AddModule(mesh);
    //obj.AddModule(collision);

    Vector3 Postion{ 0,0,-5 };
    Vector3 Rotation(0, 30, 40);
    Vector3 Scale{ 0.8f,0.8f,0.8f };
    Vector3 Color{ 0,0,1 };

    Object* sphere = Primitives::Sphere(Postion, Rotation, Scale, Color);

    Bind LeftMove; LeftMove.KeyboardBind(std::vector<void(*)()>{LeftMoveCamera}, { EnumKeyStates::KeyHold }, { sf::Keyboard::A });
    Bind RightMove; RightMove.KeyboardBind(std::vector<void(*)()>{RightMoveCamera}, { EnumKeyStates::KeyHold }, { sf::Keyboard::D });

    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::W });
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::S });

    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::E });
    
    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, MouseKeepMoved);

    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Keyboard::Escape });
    Bind CloseGameSecondMethod; CloseGameSecondMethod.MouseButtonsBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Mouse::Left }, { sf::Event::EventType::Closed });
    
    
    InpSys->InsertBind(CameraRot);

    InpSys->InsertBind(LeftMove);
    InpSys->InsertBind(RightMove);

    InpSys->InsertBind(ForwardMove);
    InpSys->InsertBind(BackwardMove);

    InpSys->InsertBind(UpMove);
    InpSys->InsertBind(DownMove);
    
    InpSys->InsertBind(CloseGameFirstMethod);
    InpSys->InsertBind(CloseGameSecondMethod);
}

void GameFunction::Update() {
    obj.SetPosition(0, 0, -3);
    obj.SetRotation(0, obj.GetRotation().Y + 1.5, 90);
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

void ForwardMoveCamera() {
    Vector3 newPos = Player.GetPosition();
    
    Vector3 UpVector{0,0,0};

    UpVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    UpVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    UpVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += UpVector * 0.1;

    Player.SetPosition(newPos);
}
void BackwardMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector{0,0,0};

    UpVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    UpVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    UpVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += UpVector * (-0.1);

    Player.SetPosition(newPos);
}

void UpMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    newPos.Y += 0.1;

    Player.SetPosition(newPos);
}
void DownMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    newPos.Y -= 0.1;

    Player.SetPosition(newPos);
}

void CameraRotate() {
    float sensitive = 0.15;

    if (InpSys->GetMouseClass()->IsMouseChangePosition()) {

        Vector3 delta = { InpSys->GetMouseClass()->GetMouseDelta().XPos,InpSys->GetMouseClass()->GetMouseDelta().YPos };

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

    InpSys->Screen = render->GetScreenClass()->GetScreen();

    camera->GetDirectionOfView();
    
    while (!World::GetStateOfGame())
    {
        InpSys->IO_Events();
        Game->Update();
       render->RenderLoop(camera);   
    }
}
