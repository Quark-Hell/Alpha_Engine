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

#include "ShadersProgram/ShaderProgram.h"
#include "ShadersProgram/OpaqueShader.h"
#include "ShadersProgram/CubeMapShader.h"
#include "ShadersProgram/PathShader.h"

#include "Texture.h"

std::shared_ptr<Object> CubeMapObj;

Object Player;
std::shared_ptr<Camera> camera = std::make_shared<Camera>();

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;
float moveSensitive = 0.40f;



std::shared_ptr<Object> Sun;
std::shared_ptr<Object> Planet1;
std::shared_ptr<Object> Planet2;


PointLight pLight;
//DirectLight dirLight;
//SpotLight sLight;


std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();

std::shared_ptr<Object> path1 = std::make_shared<Object>();
std::shared_ptr<Object> path2 = std::make_shared<Object>();

Mesh* pathMesh1 = std::dynamic_pointer_cast<Mesh>(path1->GetModuleByType(MeshType)).get();
PathShader* pathShader1;

void GameFunction::Start() {
    Mesh* mesh;

    path1->AddModule(MeshType);
    pathMesh1 = std::dynamic_pointer_cast<Mesh>(path1->GetModuleByType(MeshType)).get();
    pathMesh1->_material->Shader = std::make_shared<PathShader>(pathMesh1->_material.get());
    pathShader1 = std::dynamic_pointer_cast<PathShader>(pathMesh1->_material->Shader).get();



    CubeMapObj = Primitives::Cube({ 0,0,0 }, Vector4(0, 0, 0, 1), Vector3(1, 1, 1));
    mesh = std::dynamic_pointer_cast<Mesh>(CubeMapObj->GetModuleByType(MeshType)).get();
    mesh->Name = "CubeMap";

    mesh->_material->Shader = std::make_shared<CubeMapShader>(mesh->_material.get());

    SetControl();

    InitSun();
    InitPlanet1();
    InitPlanet2();


    //
    //std::shared_ptr<CubeMapShader> cubeMapShad = std::make_shared<CubeMapShader>();
    //cubeMapShad->LoadTexture(
    //    "\\Textures\\CubeMap\\Right_Tex.png",
    //    "\\Textures\\CubeMap\\Left_Tex.png",
    //    "\\Textures\\CubeMap\\Top_Tex.png",
    //    "\\Textures\\CubeMap\\Bottom_Tex.png",
    //    "\\Textures\\CubeMap\\Front_Tex.png",
    //    "\\Textures\\CubeMap\\Back_Tex.png");
    //
    //mesh->_material->Shader = cubeMapShad;

    //dirLight.Name = "dirLight";
    //dirLight.color = Vector3(1, 0.988, 0.792);
    //dirLight.strength = 0.3f;

    //sLight.Name = "SpotLight";
    //
    //sLight.SetPosition(0, -1, 0);
    //sLight.AddRotation(0,0,-15);
    //sLight.color = Vector3(0.639, 0.847, 0.851);
    //sLight.strength = 8.3f;
    //sLight.CutOff = glm::cos(glm::radians(22.5f));
    //sLight.OuterCutOff = glm::cos(glm::radians(35.5f));


    World::DebugRenderEnabled = true;
    World::DebugRenderMode = (DebugRenderModes)(LinesRender | PointsRender);

    //MeshCollider* col1 = new MeshCollider; col1->Create("\\Models\\Primitives\\Sphere.fbx");
 

    //RigidBody* rb = std::dynamic_pointer_cast<RigidBody>(plane3->GetModuleByType(RigidBodyType)).get();
    //rb->Gravity = Vector3(0, -1, 0);
}

void GameFunction::Update() {
    Sun->AddRotation(0.02, -0.1, 0);
    Sun->AddRotation(0.1, 0.2, 0);
    Planet1->AddRotation(0, 0.1, 0);
    Mesh* mesh1 = std::dynamic_pointer_cast<Mesh>(Planet1->GetModuleByType(MeshType)).get();
    mesh1->AddRotation(0,3,0);
    
    Planet2->AddRotation(0, 0.3, 0);
    Mesh* mesh2 = std::dynamic_pointer_cast<Mesh>(Planet2->GetModuleByType(MeshType)).get();
    mesh2->AddRotation(0, 3, 0);

    //Path();
    //sLight.AddRotation(0, -5, 0); 
}


void Path() {
    pathShader1->AddPoint(Planet1->GetPosition());
    std::cout << "X: " << Planet1->GetPosition().X << " Y: " << Planet1->GetPosition().Y << " Z: " << Planet1->GetPosition().Z << "\n";
}

void InitSun()
{
    pLight.Name = "PointLight";

    pLight.SetPosition(0, 0, 0);
    pLight.color = Vector3(0.988, 0.792, 0.463);
    pLight.strength = 5;
    pLight.radius = 55;

    Sun = Primitives::Sphere({ 0,0,0 }, Vector4(0, 0, 0, 1), Vector3(10, 10, 10));

    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Sun->GetModuleByType(MeshType)).get();
    mesh->Name = "sun";

    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());

    mesh->_material->Shader->LoadTexture(Diffuse, "\\Textures\\suncyl1.jpg");
    mesh->_material->Shader->LoadTexture(Emission, "\\Textures\\suncyl1-grayscale.jpg");
}

void InitPlanet1()
{
    Planet1 = Primitives::Sphere({ 0,1,-20 }, Vector4(0, 0, 0, 1), Vector3(0.5f, 0.5f, 0.5));
    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Planet1->GetModuleByType(MeshType)).get();
    mesh->Name = "planet1";
    Planet1->AddOriginPosition(0,0,20);

    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());

    mesh->_material->Shader->LoadTexture(Diffuse, "\\Textures\\Planets\\planet_lava_Base_Color.jpg");
    mesh->_material->Shader->LoadTexture(Emission, "\\Textures\\Planets\\planet_lava_Emissive.png");
}

void InitPlanet2()
{
    Planet2 = Primitives::Sphere({ -30,-1,-20 }, Vector4(0, 0, 0, 1), Vector3(1.0f, 1.0f, 1.0f));
    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Planet2->GetModuleByType(MeshType)).get();
    mesh->Name = "planet2";
    Planet2->AddOriginPosition(30, 0, 20);

    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());

    mesh->_material->Shader->LoadTexture(Diffuse, "\\Textures\\Planets\\planet_continental_Base_Color.jpg");
}

void SetControl() {
    Player.AddPosition(0, 0, -40);
    Player.AddModule(std::static_pointer_cast<Module>(camera));
    
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

    newPos += UpVector * moveSensitive;

    Player.SetPosition(newPos);
}
void RightMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 UpVector;

    UpVector.X = sin((Player.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sin((Player.GetRotation().Y) * 3.14159 / 180);

    newPos += UpVector * (-moveSensitive);

    Player.SetPosition(newPos);
}

void ForwardMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 ForwardVector{ 0,0,0 };

    ForwardVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += ForwardVector * moveSensitive;

    Player.SetPosition(newPos);
}
void BackwardMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    Vector3 BackwardVector{ 0,0,0 };

    BackwardVector.X = sin((Player.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.Y = cos((Player.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.Z = sin((Player.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += BackwardVector * (-moveSensitive);

    Player.SetPosition(newPos);
    //Player.AddPosition(0, 0, -0.01f);
}

void UpMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    newPos.Y += moveSensitive;

    Player.SetPosition(newPos);
}
void DownMoveCamera() {
    Vector3 newPos = Player.GetPosition();

    newPos.Y -= moveSensitive;

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
