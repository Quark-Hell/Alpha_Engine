// ALPHA_Engine.cpp : Defines the entry point for the application.
//

#include "ALPHA_Engine.h"

#include "Basical_Type.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"

#include "GameModels.cpp"
#include "Physics.cpp"
#include "Camera.cpp"
#include "Collision.cpp"

#include "Binds.cpp"

#include <ctime>

Object Player;
Camera* camera = new Camera;

GameFunction* Game = new GameFunction;
Render* render = new Render;
Collision* collision = new Collision;
InputSystem* InpSys = new InputSystem;

Object object;

void GameFunction::Start() {
    SetControl();

    Mesh* mesh = new Mesh;
    mesh->Create("\\Models\\TestModel.fbx");
    object.AddModule(mesh);

    object.SetScale(1,1,1);
    object.AddPosition(1,0,0);
    object.AddRotation(90,0,0);

    object.ApplyTransform();
}

void GameFunction::Update() {
    object.AddRotation(1.5,1.5,0);
    object.ApplyTransform();
    printf("%f\n", abs(sin(World::GetTimeLong())));

    object.SetScale(
        abs(sin(World::GetTimeLong() / 350) + 1),
        abs(sin(World::GetTimeLong() / 350) + 1),
        abs(sin(World::GetTimeLong() / 350) + 1));

    object.ApplyTransform();
}

void SetControl() {
    Player.AddModule(camera);

    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::D });

    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { sf::Keyboard::W, sf::Keyboard::LShift });
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::S });

    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::E });

    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));

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

    Vector3 ForwardVector{ 0,0,0 };

    ForwardVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += ForwardVector * 0.1;

    Player.SetPosition(newPos);
}
void BackwardMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 BackwardVector{ 0,0,0 };

    BackwardVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += BackwardVector * (-0.1);

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

        Vector3 delta;
        delta.X = InpSys->GetMouseClass()->GetMouseDelta().XPos;
        delta.Y = InpSys->GetMouseClass()->GetMouseDelta().YPos;

        if (delta.GetMagnitude() < 100) {
            Vector3 newRot = Player.GetRotation();

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
        World::StartFrame();
        InpSys->IO_Events();
        Game->Update();
        collision->CollisionLoop();
        render->RenderLoop(camera);
        World::EndFrame();
    }
}
