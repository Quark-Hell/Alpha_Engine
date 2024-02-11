// ALPHA_Engine.cpp : Defines the entry point for the application.
//
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
#include "Modules/Collider.h"
#include "Modules/BoxCollider.h"
#include "Modules/MeshCollider.h"
#include "Modules/Transform.h"

#include "Modules/Light/DirectLight.h"
#include "Modules/Light/PointLight.h"
#include "Modules/Light/SpotLight.h"

#include "Texture.h"

Object Player;
std::shared_ptr<Camera> camera = std::make_shared<Camera>();

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;

std::shared_ptr<Object> plane3;
std::shared_ptr<Object> plane2;

std::shared_ptr<Object> plane1;

DirectLight dirLight;
SpotLight sLight;
PointLight pLight;


std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();

void GameFunction::Start() {
    SetControl();

    dirLight.Name = "dirLight";
    dirLight.color = Vector3(1, 0.988, 0.792);
    dirLight.strength = 0.3f;

    sLight.Name = "SpotLight";
    
    sLight.SetPosition(0, -1, 0);
    sLight.AddRotation(0,0,-15);
    sLight.color = Vector3(0.639, 0.847, 0.851);
    sLight.strength = 8.3f;
    sLight.CutOff = glm::cos(glm::radians(22.5f));
    sLight.OuterCutOff = glm::cos(glm::radians(35.5f));

    pLight.Name = "PointLight";
    
    pLight.SetPosition(0, 3, 0);
    pLight.color = Vector3(0.639, 0.847, 0.851);
    pLight.strength = 30.3f;
    pLight.radius = 6;

    World::DebugRenderEnabled = true;
    World::DebugRenderMode = (DebugRenderModes)(LinesRender | PointsRender);

    //MeshCollider* col1 = new MeshCollider; col1->Create("\\Models\\Primitives\\Sphere.fbx");
    Vector3 pos = Vector3{ 0,0,-15 };
    Vector3 rot = Vector3{ 0,0,0 };
    Vector3 scale = Vector3{ 1,1,1 };

    plane1 = Primitives::Cube({ 0,0,0 }, rot, scale);
    plane1->AddRotation(90, 0, 0);
    plane1->SetScale(10, 10, 0.1f);
    plane1->AddPosition(0, -2, 0);
    plane1->AddModule(MeshColliderType);
 

    plane2 = Primitives::Cube({ 0,1,-3 }, rot, scale);
    plane2->SetScale(0.5f, 0.5f, 0.5f);
    plane2->AddModule(MeshColliderType);
    plane2->AddModule(RigidBodyType);


    plane3 = Primitives::Sphere({ 0,0,0 }, rot, scale);
    plane3->SetScale(0.5f, 0.5f, 0.5f);
    plane3->AddModule(MeshColliderType);
    plane3->AddModule(RigidBodyType);
    //RigidBody* rb = std::dynamic_pointer_cast<RigidBody>(plane3->GetModuleByType(RigidBodyType)).get();
    //rb->Gravity = Vector3(0, -1, 0);




    //
    //plane = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    //plane->AddModule(std::static_pointer_cast<Module>(col3));
    //plane->AddPosition(0, 5, -10);
    //plane->AddRotation(90, 0, 0);
    //plane->SetScale(5, 5, 0.5);
    //// 
    //plane->AddOriginPosition(-2.5,0,0);

    //object2 = Primitives::Cube({ 0,0,0 }, rot, scale, color);
    //object2->AddModule(std::static_pointer_cast<Module>(col2));
    ////object2->AddModule(std::static_pointer_cast<Module>(rb2));
    //object2->AddRotation(0, 0, 20);
    //object2->AddPosition(-2.5, 9, -10);
    //object2->SetScale(1, 1, 1);

    //Mesh* mesh = (Mesh*)(object2->GetModuleByType(MeshType).get());
    //Material* mat = (Material*)mesh->GetSubModuleByType(MaterialType).get();

    //ambLight.AddPosition(0, -8, 0);
}

void GameFunction::Update() {
    sLight.AddRotation(0, -5, 0); 
    //plane2->AddRotation(0, -5, 0);

      //plane1->AddRotation({ 0, 0, -0.5 });
      //plane2->AddRotation({ 0, -0.5, 0 });
      //plane3->AddRotation({ 0, -0.5, 0 });
    //plane->AddRotation({ 0, 0, -0.5 });
    //plane->AddLocalRot(Vector3{ -2.5, 0, 0 }, Vector3{ 0, 0, -0.5 });

    //object->SetScale(
    //    abs(sin(World::GetTimeLong() / 350) + 1.2),
    //    abs(sin(World::GetTimeLong() / 350) + 1.2),
    //    abs(sin(World::GetTimeLong() / 350) + 1.2));

    //std::cout << object->GetPosition().Z;
    //std::cout << "\n";
}

void SetControl() {
    Player.AddModule(std::static_pointer_cast<Module>(camera));
    //Player.AddRotation(30, 0, 0);
    Player.AddPosition(0, 0, -3);
    
    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_D });
    
    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { GLFW_KEY_W, GLFW_KEY_LEFT_SHIFT});
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_S });
    
    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_E });
    
    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));
    
    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { GLFW_KEY_ESCAPE });
    
    Bind jump; jump.KeyboardBind({ Jump }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_SPACE });
    Bind stop; stop.KeyboardBind({ Stop }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_L });

    Bind toLeft; toLeft.KeyboardBind({ LeftMoveTestObject }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_G });
    Bind toRight; toRight.KeyboardBind({ RightMoveTestObject }, { EnumKeyStates::KeyPressed }, { GLFW_KEY_H });

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
    //Player.AddPosition(0, 0, -0.01f);
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
    //object2->AddPosition(-0.02,0,0);
}
void RightMoveTestObject() {
    //object2->AddPosition(0.02, 0, 0);
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
    rb2->AddForce(10, 0, 0);
}
void Jump() {
    rb2->AddForce(0,10,0);
    printf("jump");
}

int main()
{
    //HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, 1);

    render->StartRender(camera);
    Game->Start();

    InpSys->Window = render->GetScreenClass()->GetWindow();

    render->CompileShaders();

    //World::CreateWorldTree();
    
    while (!World::GetStateOfGame())
    {
        World::StartFrame();
        Game->Update();
        InpSys->IO_Events();
        World::ApplyingSceneTransformation();
        camera->ApplyTransformation();
        Physics::PhysicsLoop();
        Collision::CollisionLoop();
        //Physics::PullingVectorsLoop();
        render->RenderLoop(camera);
        World::EndFrame();
        std::cout << World::GetTimeLong() << " timeLong\t" << World::GetDeltaTime() << " deltaTime\t" << "\n";
        //std::cout << "X: " << plane2->GetPosition().X << " Y:" << plane2->GetPosition().Y << " Z:" << plane2->GetPosition().Z << "\n";
    }

    glfwTerminate();
}
