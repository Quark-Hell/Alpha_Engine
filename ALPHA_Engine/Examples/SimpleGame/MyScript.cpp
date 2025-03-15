#include "MyScript.h"

//===================Core===================//
#include "Core/World.h"
#include "Core/Object.h"
#include "Core/Factory.h"

#include "Core/Timer.h"

#include "Core/Logger/Logger.h"
//===================Core===================//

#include "UserScriptsRegister/UserScriptConfig.h"
#include "WindowsManager/WindowsManagerConfig.h"
#include "BindsEngine/BindsEngineConfig.h"

//===================Anomaly Engine===================//
#include "AnomalyEngine/RenderEngine.h"

#include "AnomalyEngine/Buffers/CamerasBuffer.h"
#include "AnomalyEngine/Buffers/MeshesBuffer.h"
#include "AnomalyEngine/Buffers/DirectLightsBuffer.h"
#include "AnomalyEngine/Buffers/PointLightsBuffer.h"

#include "AnomalyEngine/Components/Mesh.h"
#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/DirectLight.h"
#include "AnomalyEngine/Components/PointLight.h"

#include "AnomalyEngine/Shaders/CubeMapShader.h"
#include "AnomalyEngine/Shaders/OpaqueShader.h"
#include "AnomalyEngine/Shaders/SimplexFractalShader.h"
//===================Anomaly Engine===================//

//===================User Scripts Register===================//
Register::Registry* userScriptSystem;
Register::UserScriptsBuffer* userScriptsBuffer;
//===================User Scripts Register===================//

//===================Binds Engine===================//
BindsEngine::KeyboardSystem* keyboardSystem;
BindsEngine::KeyboardSensors* keyboardBuffer;

BindsEngine::MouseSystem* mouseSystem;
BindsEngine::MouseSensors* mouseBuffer;

BindsEngine::InputSystem* inputSystem;
BindsEngine::BindsBuffer* bindsBuffer;
//===================Binds Engine===================//

//===================Windows Manager===================//
WindowsManager::WindowsManager* windowsSystem;
WindowsManager::WindowsBuffer* windowsBuffer;
//===================Windows Manager===================//

//===================Anomaly Engine===================//
AnomalyEngine::RenderEngine* anomalySystem;
AnomalyEngine::MeshesBuffer* meshesBuffer;
AnomalyEngine::CamerasBuffer* camerasBuffer;
AnomalyEngine::DirectLightsBuffer* directLightsBuffer;
AnomalyEngine::PointLightsBuffer* pointLightsBuffer;
//===================Anomaly Engine===================//

namespace Core {
    //This function will be invoked before general cycle
    //Use this for initialize global data
    void InstanceModule() {
        userScriptSystem = new Register::Registry();
        userScriptsBuffer = new Register::UserScriptsBuffer();

        keyboardSystem = new BindsEngine::KeyboardSystem();
        keyboardBuffer = new BindsEngine::KeyboardSensors();

        mouseSystem = new BindsEngine::MouseSystem();
        mouseBuffer = new BindsEngine::MouseSensors();

        inputSystem = new BindsEngine::InputSystem();
        bindsBuffer = new BindsEngine::BindsBuffer();

        windowsSystem = new WindowsManager::WindowsManager();
        windowsBuffer = new WindowsManager::WindowsBuffer();

        anomalySystem = new AnomalyEngine::RenderEngine();
        meshesBuffer = new AnomalyEngine::MeshesBuffer();
        camerasBuffer = new AnomalyEngine::CamerasBuffer();
        directLightsBuffer = new AnomalyEngine::DirectLightsBuffer();
        pointLightsBuffer = new AnomalyEngine::PointLightsBuffer();

        /*auto* script =*/ userScriptsBuffer->CreateActor<MyScript>();
    }
}

void MyScript::CameraRotate() {
    if (win1->GetCursorVisible() == true)
        return;

    double sensitive = 7;
    sensitive *= Core::World::GetDeltaTime();

    Core::SystemData *mouseData = Core::World::GetSystemData("MouseSensorsBuffer");
    auto mouse = reinterpret_cast<BindsEngine::MouseSensors*>(mouseData);

    if (mouse->IsMouseChangePosition()) {

        glm::vec2 delta;
        delta.x = mouse->GetMouseDelta().x;
        delta.y = mouse->GetMouseDelta().y;

        glm::vec3 newRot = Player->transform.GetRotation();

        newRot.x += delta.y * sensitive;
        newRot.y += delta.x * sensitive;

        Player->transform.SetRotation(newRot);

    }
}

void MyScript::ShowCursor() {
    std::cout << "Show";
    win1->SetCursorVisible(true);
}

void MyScript::HideCursor() {
    win1->SetCursorVisible(false);
}

void MyScript::LeftMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 UpVector;

    UpVector.x = sinf((Player->transform.GetRotation().y + 90) * 3.14159 / 180);
    UpVector.y = 0;
    UpVector.z = sinf((Player->transform.GetRotation().y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::RightMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 UpVector;

    UpVector.x = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180);
    UpVector.y = 0;
    UpVector.z = sin((Player->transform.GetRotation().y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * (-sensitive);

    Player->transform.SetPosition(newPos);
}

void MyScript::ForwardMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 ForwardVector{ 0,0,0 };

    ForwardVector.x = sin((Player->transform.GetRotation().y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.y = cos((Player->transform.GetRotation().x + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.z = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += ForwardVector * sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::BackwardMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 BackwardVector{ 0,0,0 };

    BackwardVector.x = sin((Player->transform.GetRotation().y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.y = cos((Player->transform.GetRotation().x + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.z = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += BackwardVector * (-sensitive);

    Player->transform.SetPosition(newPos);
}

void MyScript::UpMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y += sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::DownMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y -= sensitive;

    Player->transform.SetPosition(newPos);
}


void MyScript::PushUp() {
   //glm::vec2 size = win1->GetRectangleSize(0);
   //size.y += 255.0 * Core::World::GetDeltaTime();

   //win1->PushLeftRectEdge(size, 0);
}
void MyScript::PushDown() {
   //glm::vec2 size = win1->GetRectangleSize(0);
   //size.y -= 255.0 * Core::World::GetDeltaTime();

   //win1->PushLeftRectEdge(size, 0);
}

void MyScript::PushRight() {
   float delta = -0.2f;
   delta *= Core::World::GetDeltaTime();

    {
        Core::ScopedTimer timer("timer");
        win1->PushRightRectEdge(-delta, *rect, nullptr, nullptr, nullptr);  // -->
    }
    std::cout << "============" << std::endl;
    //win1->PushLeftRectEdge(delta, *rect, nullptr, nullptr, nullptr);  // -->
}
void MyScript::PushLeft() {
    float delta = 0.2f;
    delta *= Core::World::GetDeltaTime();

    win1->PushRightRectEdge(-delta, *rect, nullptr, nullptr, nullptr); // <--
    std::cout << "============" << std::endl;
    //win1->PushLeftRectEdge(delta, *rect, nullptr, nullptr, nullptr);  // -->
}

void MyScript::GenerateCubeMap() {
    auto& obj2 = Core::Factory::CreateObject();
    obj2.SetName("Mesh");
    auto& mesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Cube.fbx");
    obj2.AddComponent(mesh);

    auto& shader = mesh._material.InitShader<AnomalyEngine::CubeMapShader>();
    shader.LoadTextures(
    R"(/Assets/Textures/CubeMap/Left_Tex.tga)",
    R"(/Assets/Textures/CubeMap/Right_Tex.tga)",
    R"(/Assets/Textures/CubeMap/Top_Tex.tga)",
    R"(/Assets/Textures/CubeMap/Bottom_Tex.tga)",
    R"(/Assets/Textures/CubeMap/Front_Tex.tga)",
    R"(/Assets/Textures/CubeMap/Back_Tex.tga)"
        );
}

void MyScript::GenerateLightSource() {
    auto& LightsSource = Core::Factory::CreateObject();
    LightsSource.transform.AddPosition(0,5,0);

    auto& dirLight = directLightsBuffer->CreateDirectLight();
    dirLight.Intensity = 0.1;
    LightsSource.AddComponent(dirLight);

    auto& pointLight = pointLightsBuffer->CreatePointLight();
    pointLight.Intensity = 100;
    LightsSource.AddComponent(pointLight);
}

void MyScript::GenerateEarth() {
    auto& cube = Core::Factory::CreateObject();

    cube.transform.AddPosition(0, -5, -25);
    cube.transform.AddRotation(0, 0, 0);
    cube.transform.SetScale(50, 0.5, 50);

    cube.SetName("Cube");

    auto& cubeMesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Cube.fbx");
    cube.AddComponent(cubeMesh);

    auto& shader = cubeMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
    shader.LoadTextures(
        "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/Assets/Textures/Planets/8k_earth_nightmap.jpg");
}

void MyScript::GenerateSun() {
    auto& Sun = Core::Factory::CreateObject();

    Sun.transform.AddPosition(0, 35, -55);
    Sun.transform.SetScale(15, 15, 15);

    Sun.SetName("Sun");

    auto& sunMesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Sphere.fbx");
    Sun.AddComponent(sunMesh);

    auto& shader = sunMesh._material.InitShader<AnomalyEngine::SimplexFractalShader>();
    shader.resolution = 3;
}

void MyScript::Serialization() {
    DerivedData data{10,20,30,40};
    DerivedData res{0,0,0,0};

    Core::TSerialized<DerivedData> dataBuffer;
    dataBuffer.Serialize(data);
    dataBuffer.Deserialize(res);

    Core::TSerialized<DerivedData>::SaveData(data,"/Saved.bin");
    Core::TSerialized<DerivedData>::LoadData(data,"/Saved.bin");
}
void MyScript::LogExample() {
#if LOGGER_INCLUDED
    Core::Logger::LogInfo("TestLoggerEvent");
    Core::Logger::LogWarning("TestLoggerWarning");
    Core::Logger::LogError("TestLoggerError: " + __LOGERROR__);
    //Logger::Logger::LogCritical("TestLoggerCritical: " + __LOGERROR__); //This crash Game with your error
#endif
}

void MyScript::WindowsTest1() {
    auto& cam1_1 = camerasBuffer->CreateCamera();
    auto& cam1_2 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0},{0.3,0.3});
    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    win1->CreateRectangle({0.5,0},{0.5,0.5});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player->AddComponent(cam1_1);
    Player->AddComponent(cam1_2);
}

void MyScript::WindowsTest2() {
    auto& cam1_1 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0},{0.025,0.95});
    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player->AddComponent(cam1_1);

    //------------------------------------------------//

    auto& cam1_2 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0.95},{1,0.05});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player->AddComponent(cam1_2);

    //------------------------------------------------//
    auto& cam1_3 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0.025,0.3},{0.3,0.651});
    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player->AddComponent(cam1_3);

    //------------------------------------------------//
    auto& cam1_4 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0.025,0},{0.975,0.3});
    cam1_4.SetRenderWindow(win1);
    cam1_4.SetUseRectangle(true);
    cam1_4.SetIndexRectangle(3);

    Player->AddComponent(cam1_4);

    //------------------------------------------------//
    auto& cam1_5 = camerasBuffer->CreateCamera();

    auto& rect = win1->CreateRectangle({0.355,0.4},{0.375,0.251});
    cam1_5.SetRenderWindow(win1);
    cam1_5.SetUseRectangle(true);
    cam1_5.SetIndexRectangle(4);

    Player->AddComponent(cam1_5);

    win1->RectangleFillFreeSpace(rect);
}

void MyScript::WindowsTest3() {
    auto& cam1_1 = camerasBuffer->CreateCamera();

    rect = &win1->CreateRectangle({0.3f,0.3f},{0.4f,0.4f});

    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player->AddComponent(cam1_1);

    //------------------------------------------------//

    auto& cam1_2 = camerasBuffer->CreateCamera();

    auto& rect2 = win1->CreateRectangle({0,0},{0.1f,0.1f});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player->AddComponent(cam1_2);
    win1->RectangleFillFreeSpace(rect2);

    //------------------------------------------------//

    auto& cam1_3 = camerasBuffer->CreateCamera();

    auto& rect3 = win1->CreateRectangle({0.9f,0.9f},{0.1f,0.1f});
    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player->AddComponent(cam1_3);
    win1->RectangleFillFreeSpace(rect3);

    //------------------------------------------------//

    auto& cam1_4 = camerasBuffer->CreateCamera();

    auto& rect4 = win1->CreateRectangle({0.5f,0.9f},{0.1f,0.1f});
    cam1_4.SetRenderWindow(win1);
    cam1_4.SetUseRectangle(true);
    cam1_4.SetIndexRectangle(3);

    Player->AddComponent(cam1_4);
    win1->RectangleFillFreeSpace(rect4);

    //------------------------------------------------//

    auto& cam1_5 = camerasBuffer->CreateCamera();

    auto& rect5 = win1->CreateRectangle({0.5f,0.0},{0.1f,0.1f});
    cam1_5.SetRenderWindow(win1);
    cam1_5.SetUseRectangle(true);
    cam1_5.SetIndexRectangle(4);

    Player->AddComponent(cam1_5);
    win1->RectangleFillFreeSpace(rect5);

    //------------------------------------------------//

    rect->SetPosition({0.4, 0.4});
    rect->SetSize({0.2, 0.2});
    win1->RectangleFillFreeSpace(*rect);

    rect = &rect2;

    //std::cout << "end";

    //win1->PushLeftRectEdge(-0.2f, rect1, nullptr);  // --> work
    //win1->PushLeftRectEdge(0.2f, rect1, nullptr);   // <-- work

    //win1->PushRightRectEdge(-0.2f, rect1, nullptr); // <-- work
    //win1->PushRightRectEdge(0.2f, rect1, nullptr);  // --> work
}

void MyScript::WindowsTest4() {
    auto& cam1_2 = camerasBuffer->CreateCamera();

    rect = &win1->CreateRectangle({0.0f,0.0f},{0.1f, 0.2f});

    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player->AddComponent(cam1_2);

    //------------------------------------------------//

    auto& cam1_3 = camerasBuffer->CreateCamera();

    auto& rect3 = win1->CreateRectangle({0.4f,0.0f},{0.1f, 0.2f});

    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player->AddComponent(cam1_3);

    //------------------------------------------------//

    auto& cam1_1 = camerasBuffer->CreateCamera();

    auto& rect1 = win1->CreateRectangle({0.3f,0.0f},{0.05f, 1.0f});

    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player->AddComponent(cam1_1);

    //------------------------------------------------//

    win1->RectangleFillFreeSpace(rect3);
    win1->RectangleFillFreeSpace(*rect);

    //rect = &rect3;

    std::cout << "test" << std::endl;
}

//Call after created
void MyScript::Start() {
    Serialization();
    LogExample();

    Player = &Core::Factory::CreateObject();
    Player->SetName("TestObject");

#if WINDOWS_MANAGER_INCLUDED
    const auto windowsBuffer = Core::World::GetSystemData("WindowsBuffer");
    if (windowsBuffer == nullptr) {
        Core::Logger::LogError("Failed to get windows buffer: " + __LOGERROR__);
        return;
    }
    const auto windows = reinterpret_cast<WindowsManager::WindowsBuffer*>(windowsBuffer);

    win1 = windows->CreateWindow(1280, 720, "Windows 1");
    win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace BindsEngine;

        auto* bindsBuffer = Core::World::GetSystemData("BindsBuffer");
        if (bindsBuffer == nullptr) {
            Core::Logger::LogError("BindsBuffer does not exist: " + __LOGERROR__);
            return;
        }
        auto* buffer = reinterpret_cast<BindsBuffer*>(bindsBuffer);

        /*auto& showCursor =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ShowCursor, this) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            win1);

        /*auto& hideCursor =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::HideCursor, this) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            win1
        );

        /*auto& leftMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            win1
        );

        /*auto& rightMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            win1
        );

        /*auto& forwardMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            win1
        );

        /*auto& backwardMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            win1
        );

        /*auto& upMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            win1
        );

        /*auto& downMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            win1
        );


        /*auto& rotateBind =*/ buffer->CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
            win1
        );

        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushRight, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Right },
            win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushLeft, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Left },
            win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushUp, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Up },
            win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushDown, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Down },
            win1
        );


        //bind.IsActive = false;
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    WindowsTest3();

    GenerateCubeMap();
    GenerateEarth();
    GenerateLightSource();
    GenerateSun();
#endif
}
//Call every frame
void MyScript::Update() {
    //Core::Logger::LogInfo(Core::World::GetDeltaTime());
}
//Call before deleted
void MyScript::End() {

}