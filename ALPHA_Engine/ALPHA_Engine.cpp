// ALPHA_Engine.cpp : Defines the entry point for the application.
//

#include "ALPHA_Engine.h"

#include "Basical_Type.h"
#include "Basical_Type.cpp"
#include "Graphic_Engine.cpp"

#include "GameModels.cpp"
#include "Modules/Physics.cpp"
#include "Modules/Camera.cpp"
#include "Collision.cpp"

#include "Binds.cpp"

#include <ctime>

Object Player;
Camera* camera = new Camera;

GameFunction* Game = new GameFunction;
Render* render = new Render;
Collision* collision = new Collision;
InputSystem* InpSys = new InputSystem;

Object object1;
Object object2;
Object object3;
Object object4;
Object object5;
Object object6;
Object object7;
Object object8;

bool IsRotating = true;

void GameFunction::Start() {
    SetControl();

    Mesh* mesh1 = new Mesh; mesh1->Create("\\Models\\Blender.fbx");
    Mesh* mesh2 = new Mesh; mesh2->Create("\\Models\\Blender.fbx");
    Mesh* mesh3 = new Mesh; mesh3->Create("\\Models\\Blender.fbx");
    Mesh* mesh4 = new Mesh; mesh4->Create("\\Models\\Blender.fbx");
    Mesh* mesh5 = new Mesh; mesh5->Create("\\Models\\Blender.fbx");
    Mesh* mesh6 = new Mesh; mesh6->Create("\\Models\\Blender.fbx");
    Mesh* mesh7 = new Mesh; mesh7->Create("\\Models\\Blender.fbx");
    Mesh* mesh8 = new Mesh; mesh8->Create("\\Models\\Blender.fbx");

    object1.AddModule(mesh1);
    object2.AddModule(mesh2);
    object3.AddModule(mesh3);
    object4.AddModule(mesh4);
    object5.AddModule(mesh5);
    object6.AddModule(mesh6);
    object7.AddModule(mesh7);
    object8.AddModule(mesh8);

    object1.AddPosition(0, 0, 0);
    object2.AddPosition(0, 1, 0);
    object3.AddPosition(0, 2, 0);
    object4.AddPosition(0, 3, 0);
    object5.AddPosition(0, 4, 0);
    object6.AddPosition(0, 5, 0);
    object7.AddPosition(0, 6, 0);
    object8.AddPosition(0, 7, 0);

    object1.ApplyTransform();
    object2.ApplyTransform();
    object3.ApplyTransform();
    object4.ApplyTransform();
    object5.ApplyTransform();
    object6.ApplyTransform();
    object7.ApplyTransform();
    object8.ApplyTransform();

    //object.SetScale(1,1,1);
    //object.AddPosition(0,0,0);
    //object.AddRotation(0,0,0);
    //
    //object.ApplyTransform();
}

void GameFunction::Update() {
    if (IsRotating) {
        for (size_t i = 0; i < 3; i++)
        {
            object1.AddRotation(0, 1.5, 0);
            object1.ApplyTransform();

            object2.AddRotation(0, 1.5, 0);
            object2.ApplyTransform();

            object3.AddRotation(0, 1.5, 0);
            object3.ApplyTransform();

            object4.AddRotation(0, 1.5, 0);
            object4.ApplyTransform();

            object5.AddRotation(0, 1.5, 0);
            object5.ApplyTransform();

            object6.AddRotation(0, 1.5, 0);
            object6.ApplyTransform();

            object7.AddRotation(0, 1.5, 0);
            object7.ApplyTransform();

            object8.AddRotation(0, 1.5, 0);
            object8.ApplyTransform();
        }
    }
    
    //object.SetScale(
    //    abs(sin(World::GetTimeLong() / 350) + 1),
    //    abs(sin(World::GetTimeLong() / 350) + 1),
    //    abs(sin(World::GetTimeLong() / 350) + 1));
    
    //object.ApplyTransform();
}

void Switcher() {
    IsRotating = !IsRotating;
}

void SetControl() {
    Player.AddModule(camera);

    Bind Switch; Switch.KeyboardBind({ Switcher },{EnumKeyStates::KeyPressed},{sf::Keyboard::U});

    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::D });

    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { sf::Keyboard::W, sf::Keyboard::LShift });
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::S });

    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::E });

    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));

    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Keyboard::Escape });
    Bind CloseGameSecondMethod; CloseGameSecondMethod.MouseButtonsBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Mouse::Left }, { sf::Event::EventType::Closed });

    InpSys->InsertBind(Switch);

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
