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

Object* object = new Object;

bool IsRotating = true;

void GameFunction::Start() {
    SetControl();

    Vector3 pos = Vector3{ 0,0,0 };
    Vector3 rot = Vector3{ 0,0,0 };
    Vector3 scale = Vector3{ 1,1,1 };
    Vector3 color = Vector3{ 0,0,0 };
    object = Primitives::Cube(pos, rot, scale, color);

    object->AddPosition(10, 0, 0);
    object->AddRotation(0, 30, 0);
    object->SetScale(1, 1, 1);
}

void GameFunction::Update() {
    //if (IsRotating) {
    //    for (size_t it = 0; it < objects.size(); it++)
    //    {
    //        objects[it]->AddRotation(0, 0.5, 0);
    //        objects[it]->AddPosition(sin(World::GetTimeLong() / 400) / 10, 0, 0);
    //
    //        objects[it]->SetScale(
    //            abs(sin(World::GetTimeLong() / 750) + 2),
    //            abs(sin(World::GetTimeLong() / 750) + 2),
    //            abs(sin(World::GetTimeLong() / 750) + 2));
    //
    //        //objects[it]->AddPosition(sin(World::GetTimeLong() / 350) / 15, 0, 0);
    //        //objects[it]->AddPosition(sin(World::GetTimeLong() / 350) / 15, 0, 0);
    //    }
    //}
    
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
    
    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_D });
    
    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { GLFW_KEY_W, GLFW_KEY_LEFT_SHIFT});
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_S });
    
    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_E });
    
    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));
    
    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { GLFW_KEY_ESCAPE });
    
    InpSys->InsertBind(CameraRot);
    
    InpSys->InsertBind(LeftMove);
    InpSys->InsertBind(RightMove);
    
    InpSys->InsertBind(ForwardMove);
    InpSys->InsertBind(BackwardMove);
    
    InpSys->InsertBind(UpMove);
    InpSys->InsertBind(DownMove);
    
    InpSys->InsertBind(CloseGameFirstMethod);
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
    //HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, 1);

    Game->Start();
    render->StartRender(camera);

    InpSys->Window = render->GetScreenClass()->GetWindow();

    camera->GetDirectionOfView();

    while (!World::GetStateOfGame())
    {
        World::StartFrame();
        InpSys->IO_Events();
        Game->Update();
        World::ApplyingSceneTransformation();
        collision->CollisionLoop();
        render->RenderLoop(camera);
        World::EndFrame();
    }

    glfwTerminate();
}
