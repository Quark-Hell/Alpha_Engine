// ALPHA_Engine.cpp : Defines the entry point for the application.
//
#pragma once
#include "ALPHA_Engine.h"

#include "Engine/Alghoritms.h"
#include "Engine/Basical_Type.h"

#include "Engine/World.h"
#include "Engine/Object.h"

#include "Engine/Collision.h"
#include "Engine/Graphic_Engine.h"

#include "Engine/Binds.h"
#include "Engine/AdditionalMath.h"

#include "GameModels.h"

#include "Modules/Camera.h"
#include "Modules/Geometry.h"
#include "Modules/Mesh.h"
#include "Modules/Module.h"
#include "Modules/Physics.h"
#include "Modules/ColliderPresets.h"
#include "Modules/BoxCollider.h"
#include "Modules/MeshCollider.h"
#include "Modules/Transform.h"

Object Player;
std::shared_ptr<Camera> camera = std::make_shared<Camera>();

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;


std::shared_ptr<Object> plane;
std::shared_ptr<Object> plane1;
std::shared_ptr<Object> plane3;
std::shared_ptr<Object> object2;

std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();

void GameFunction::Start() {
    SetControl();

    World::DebugRenderEnabled = true;
    World::DebugRenderMode = (DebugRenderModes)(LinesRender | PointsRender);

    //MeshCollider* col1 = new MeshCollider; col1->Create("\\Models\\Primitives\\Sphere.fbx");
    auto col2 = std::make_shared<BoxCollider>();
    auto col3 = std::make_shared<BoxCollider>();
    auto col4 = std::make_shared<BoxCollider>();
    auto col5 = std::make_shared<BoxCollider>();

    Vector3 pos = Vector3{ 0,0,-15 };
    Vector3 rot = Vector3{ 0,0,0 };
    Vector3 scale = Vector3{ 1,1,1 };
    Vector3 color = Vector3{ 0,0,0 };

    //object = Primitives::Sphere(pos, rot, scale, color);
    //object->AddModule(col1);
    //object->AddModule(rb1);
    //object->AddPosition(9, 3, 0);
    //rb1->CalculateCenterMass();


    
    plane3 = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    plane3->AddModule(std::static_pointer_cast<Module>(col5));
    plane3->AddPosition(-3, 0, -10);
    plane3->AddRotation(0, 0, 10);
    plane3->SetScale(3, 3, 0.5);

    plane1 = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    plane1->AddModule(std::static_pointer_cast<Module>(col4));
    plane1->AddPosition(-0.5, -2, -10);
    plane1->AddRotation(90, 0, 0);
    plane1->SetScale(10, 10, 0.5);

    plane = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    plane->AddModule(std::static_pointer_cast<Module>(col3));
    plane->AddPosition(0, 5, -10);
    plane->AddRotation(90, 30, 60);
    plane->SetScale(5, 5, 0.5);

    object2 = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    object2->AddModule(std::static_pointer_cast<Module>(col2));
    object2->AddModule(std::static_pointer_cast<Module>(rb2));
    object2->AddRotation(0, 0, 0);
    object2->AddPosition(-2.1f, 4, -10);
    object2->SetScale(1, 1, 1);
}

void GameFunction::Update() {
    //object->AddRotation(1.5,0,0);

    //object->SetScale(
    //    abs(sin(World::GetTimeLong() / 350) + 1.2),
    //    abs(sin(World::GetTimeLong() / 350) + 1.2),
    //    abs(sin(World::GetTimeLong() / 350) + 1.2));

    //std::cout << object->GetPosition().Z;
    //std::cout << "\n";
}

void SetControl() {
    Player.AddModule(std::static_pointer_cast<Module>(camera));
    Player.AddRotation(20, 0, 0);
    Player.AddPosition(0, -7, 0);
    
    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_D });
    
    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { GLFW_KEY_W, GLFW_KEY_LEFT_SHIFT});
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_S });
    
    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_E });
    
    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));
    
    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { GLFW_KEY_ESCAPE });
    
    Bind jump; jump.KeyboardBind({ Jump }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_SPACE });
    Bind stop; stop.KeyboardBind({ Stop }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_G });

    Bind toLeft; toLeft.KeyboardBind({ LeftMoveTestObject }, { EnumKeyStates::KeyHold }, { GLFW_KEY_H });
    Bind toRight; toRight.KeyboardBind({ RightMoveTestObject }, { EnumKeyStates::KeyHold }, { GLFW_KEY_J });

    InpSys->InsertBind(toLeft);
    InpSys->InsertBind(toRight);

    InpSys->InsertBind(CameraRot);
    
    InpSys->InsertBind(LeftMove);
    InpSys->InsertBind(RightMove);
    
    InpSys->InsertBind(ForwardMove);
    InpSys->InsertBind(BackwardMove);
    
    InpSys->InsertBind(UpMove);
    InpSys->InsertBind(DownMove);
    
    InpSys->InsertBind(CloseGameFirstMethod);

    InpSys->InsertBind(stop);
    InpSys->InsertBind(jump);
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

void LeftMoveTestObject() {
    object2->AddPosition(-0.02,0,0);
}
void RightMoveTestObject() {
    object2->AddPosition(0.02, 0, 0);
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

void Stop() {
    //rb1->AddForce(0, 100, 0);
}
void Jump() {
    //rb1->AddForce(-0.2,0,0);
    printf("jump");
}

int main()
{
    //HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, 1);

    Game->Start();
    render->StartRender(camera);
    
    InpSys->Window = render->GetScreenClass()->GetWindow();
    
    while (!World::GetStateOfGame())
    {
        World::StartFrame();
        Game->Update();
        InpSys->IO_Events();
        World::ApplyingSceneTransformation();
        Physics::PhysicsLoop();
        Collision::CollisionLoop();
        //Physics::PullingVectorsLoop();
        render->RenderLoop(camera);
        World::EndFrame();
        std::cout << World::GetTimeLong() << " timeLong\t" << World::GetDeltaTime() << " deltaTime\t" << "\n";
    }

    glfwTerminate();
}
