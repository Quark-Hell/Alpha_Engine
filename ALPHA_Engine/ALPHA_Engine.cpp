// ALPHA_Engine.cpp : Defines the entry point for the application.
//
#include "ALPHA_Engine.h"
#include "MemoryManager.h"

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
#include "ShadersProgram/ColliderWireframeShader.h"

#include "Texture.h"


Object Player;
std::shared_ptr<Camera> camera = std::make_shared<Camera>();

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;
float moveSensitive = 0.40f;


std::shared_ptr<Object> Sun;
std::shared_ptr<Object> Planet1;
std::shared_ptr<Object> Planet2;

std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();




Mesh* pathMesh1 = new Mesh();
PathShader* pathShader1;



Mesh* pathMesh2 = new Mesh();
PathShader* pathShader2;

void GameFunction::Start() {
    std::chrono::steady_clock::time_point _startTime = std::chrono::high_resolution_clock::now();

    Mesh* mesh;
    mesh = std::dynamic_pointer_cast<Mesh>(World::SkyBox->GetModuleByType(MeshType)).get();
    mesh->_material->Shader = std::make_shared<CubeMapShader>(mesh->_material.get());

    SetControl();

    InitPlanet1();
    InitSun();

    InitPlanet2();

    World::DebugRenderEnabled = true;
    World::DebugRenderMode = (DebugRenderModes)(LinesRender | PointsRender);

    std::chrono::steady_clock::time_point _endTime = std::chrono::high_resolution_clock::now();
    float _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(_endTime - _startTime).count() * 0.000001f;
    std::cout << "work time: " << _deltaTime << "\n";
}

void GameFunction::Update() {
    Sun->AddRotation(0.02, -0.1, 0);
    Sun->AddRotation(0.1, 0.2, 0);
    Planet1->AddRotation(0, 0.1, 0);
    Mesh* mesh1 = std::dynamic_pointer_cast<Mesh>(Planet1->GetModuleByType(MeshType)).get();
    mesh1->AddRotation(0, 3, 0);

    Planet2->AddRotation(0, 0.3, 0);
    Mesh* mesh2 = std::dynamic_pointer_cast<Mesh>(Planet2->GetModuleByType(MeshType)).get();
    mesh2->AddRotation(0, 3, 0);

    Path(Planet1.get(), pathShader1);
    Path(Planet2.get(), pathShader2);
}


void Path(Object* object, PathShader* shader) {
    glm::vec4 p;
    p.x = object->GetPosition().X;
    p.y = object->GetPosition().Y;
    p.z = object->GetPosition().Z;
    p.w = 1;

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * object->GetRotation().X;
    const float radY = M_PI / 180 * object->GetRotation().Y;
    const float radZ = M_PI / 180 * object->GetRotation().Z;

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    p = rotMat * p;

    Vector3 point = Vector3(p.x, p.y, p.z);

    shader->AddPoint(point);
}

//std::shared_ptr<Object> obj;
void InitSun()
{
    //obj = Primitives::Cube(Vector3(0, 0, 0), Vector4(0, 0, 0, 1), Vector3(1, 1, 1));
    //Mesh* aabb = std::dynamic_pointer_cast<Mesh>(obj->GetModuleByType(MeshType)).get();
    //aabb->_material->Shader = std::make_shared<ColliderWireframeShader>(aabb->_material.get());

    PointLight* pLight = new PointLight();
    pLight->Name = "PointLight";

    pLight->SetPosition(0, 0, 0);
    pLight->color = Vector3(0.988, 0.792, 0.463);
    pLight->strength = 5;
    pLight->radius = 55;

    Sun = Primitives::Sphere(Vector3(0, 0, 0), Vector4(0, 0, 0, 1), Vector3(10, 10, 10));

    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Sun->GetModuleByType(MeshType)).get();
    mesh->Name = "sun";

    //
    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());

    //mesh->_material->Shader->AsyncLoadTexture(Diffuse, "\\Textures\\suncyl1.jpg");
    OpaqueShader* opShader = std::dynamic_pointer_cast<OpaqueShader>(mesh->_material->Shader).get();
    opShader->LoadTexture("\\Textures\\suncyl1.tga", "", "", "", "", "\\Textures\\suncyl1-grayscale.bmp", "", "", "");

}

void InitPlanet1()
{
    Planet1 = Primitives::Sphere({ 0,0,-20 }, Vector4(0, 0, 0, 1), Vector3(0.5f, 0.5f, 0.5));
    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Planet1->GetModuleByType(MeshType)).get();
    mesh->Name = "planet1";
    Planet1->AddOriginPosition(0, 0, 20);

    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());

    OpaqueShader* opShader = std::dynamic_pointer_cast<OpaqueShader>(mesh->_material->Shader).get();
    opShader->LoadTexture("\\Textures\\Planets\\planet_lava_Base_Color.tga", "", "", "", "", "\\Textures\\Planets\\planet_lava_Emissive.tga", "", "", "");

    Object* path1 = new Object();
    path1->AddModule(MeshType);
    pathMesh1 = std::dynamic_pointer_cast<Mesh>(path1->GetModuleByType(MeshType)).get();
    pathMesh1->_material->Shader = std::make_shared<PathShader>(pathMesh1->_material.get());
    pathShader1 = std::dynamic_pointer_cast<PathShader>(pathMesh1->_material->Shader).get();
}

void InitPlanet2()
{
    Planet2 = Primitives::Sphere({ -30,0,-20 }, Vector4(0, 0, 0, 1), Vector3(1.0f, 1.0f, 1.0f));
    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(Planet2->GetModuleByType(MeshType)).get();
    mesh->Name = "planet2";
    Planet2->AddOriginPosition(30, 0, 20);

    mesh->_material->Shader = std::make_shared<OpaqueShader>(mesh->_material.get());
    mesh->_material->Shader->LoadTexture(Diffuse, "\\Textures\\Planets\\planet_continental_Base_Color.tga");

    Object* path2 = new Object();
    path2->AddModule(MeshType);
    pathMesh2 = std::dynamic_pointer_cast<Mesh>(path2->GetModuleByType(MeshType)).get();
    pathMesh2->_material->Shader = std::make_shared<PathShader>(pathMesh2->_material.get());
    pathShader2 = std::dynamic_pointer_cast<PathShader>(pathMesh2->_material->Shader).get();
}

void SetControl() {
    Player.AddPosition(0, 0, -40);
    Player.AddModule(std::static_pointer_cast<Module>(camera));

    Bind LeftMove; LeftMove.KeyboardBind({ LeftMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_A });
    Bind RightMove; RightMove.KeyboardBind({ RightMoveCamera }, { EnumKeyStates::KeyHold }, { GLFW_KEY_D });

    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { GLFW_KEY_W, GLFW_KEY_LEFT_SHIFT });
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
    render->StartRender(camera);
    World::Init();
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
    }

    glfwTerminate();
}
