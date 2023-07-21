// ALPHA_Engine.cpp : Defines the entry point for the application.
//

#include "ALPHA_Engine.h"

#include "Engine/Basical_Type.h"

#include "Engine/Alghoritms.cpp"
#include "Engine/Collision.cpp"
#include "Engine/Graphic_Engine.cpp"

#include "Engine/World.cpp"
#include "Engine/Object.cpp"

#include "Engine/Binds.cpp"
#include "Engine/AdditionalMath.cpp"

#include "GameModels.cpp"

#include "Modules/Camera.cpp"
#include "Modules/Geometry.cpp"
#include "Modules/Mesh.cpp"
#include "Modules/Module.cpp"
#include "Modules/Physics.cpp"
#include "Modules/ColliderPresets.cpp"
#include "Modules/BoxCollider.cpp"

Object Player;
Camera* camera = new Camera;

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;

Object* object = new Object;
Object* object2 = new Object;

Object* plane = new Object;


RigidBody* rb2 = new RigidBody;

void GameFunction::Start() {
    SetControl();

    MeshCollider* col1 = new MeshCollider; col1->Create("\\Models\\Primitives\\Sphere.fbx");
    MeshCollider* col2 = new MeshCollider; col2->Create("\\Models\\Primitives\\Sphere.fbx");

    MeshCollider* col3 = new MeshCollider; col3->Create("\\Models\\Primitives\\Cube.fbx");

    BoxCollider* bx = new BoxCollider;

    Vector3 pos = Vector3{ 0,0,-15 };
    Vector3 rot = Vector3{ 0,0,0 };
    Vector3 scale = Vector3{ 1,1,1 };
    Vector3 color = Vector3{ 0,0,0 };

    //object = Primitives::Sphere(pos, rot, scale, color);
    //object->AddModule(col1);
    //object->AddModule(rb1);
    //object->AddPosition(9, 3, 0);
    //rb1->CalculateCenterMass();

    plane = Primitives::Cube(pos, rot, scale, color);
    //plane->AddModule(col3);
    plane->AddModule(bx);
    plane->AddPosition(0, -5, 5);
    plane->AddRotation(90, 0, 0);
    plane->SetScale(10, 10, 0.5);

    object2 = Primitives::Sphere(pos, rot, scale, color);
    object2->AddModule(col2);
    object2->AddModule(rb2);
    object2->AddPosition(-2, 3, 0);
    rb2->CalculateCenterMass();
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
    Player.AddModule(camera);
    
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

    camera->GetDirectionOfView();

    while (!World::GetStateOfGame())
    {
        World::StartFrame();
        Game->Update();
        InpSys->IO_Events();
        World::ApplyingSceneTransformation();
        Physics::PhysicsLoop();
        Collision::CollisionLoop();
        render->RenderLoop(camera);
        World::EndFrame();
        //std::cout << World::GetTimeLong() << "\t" << World::GetDeltaTime() << "\n";
    }

    glfwTerminate();
}
