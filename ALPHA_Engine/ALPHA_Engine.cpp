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

Object obj;

Object Player;
Camera* camera = new Camera;

Object* Cube1;
Object* Cube2;

GameFunction* Game = new GameFunction;
Render* render = new Render;
InputSystem* InpSys = new InputSystem;

void GameFunction::Start() {

    Player.AddModule(camera);

    Mesh* mesh = new Mesh;
    mesh->Create("\\Models\\Blender.fbx");
    obj.AddModule(mesh);
    obj.AddScale(1, 1, 1);

    Vector3 Postion{ 0,0,0 };
    Vector3 Rotation(0, 0, 0);
    Vector3 Scale{ 1,1,1 };
    Vector3 Color{ 0,0,1 };

    Collider* col1 = new Collider;
    Collider* col2 = new Collider;

    col1->Create("\\Models\\Primitives\\Cube.fbx");
    col2->Create("\\Models\\Primitives\\Cube.fbx");

    col1->Rename("Collider");
    col2->Rename("Collider");

    Cube1 = Primitives::Cube(Postion, Rotation, Scale, Color);
    Cube2 = Primitives::Cube(Postion, Rotation, Scale, Color);

    Cube1->ApplyTransform();
    Cube2->ApplyTransform();

    Cube1->AddModule(col1);
    Cube2->AddModule(col2);

    Cube2->AddPosition(0,0,1);

    Cube1->ApplyTransform();
    Cube2->ApplyTransform();

    Bind LeftCubeMove; LeftCubeMove.KeyboardBind({LeftMoveTestObject}, { EnumKeyStates::KeyHold }, { sf::Keyboard::Left });
    Bind RightCubeMove; RightCubeMove.KeyboardBind({RightMoveTestObject}, { EnumKeyStates::KeyHold }, { sf::Keyboard::Right });

    Bind ForwardCubeMove; ForwardCubeMove.KeyboardBind({ ForwardMoveTestObject }, { EnumKeyStates::KeyHold }, { sf::Keyboard::N });
    Bind BackwardCubeMove; BackwardCubeMove.KeyboardBind({ BackwardMoveTestObject }, { EnumKeyStates::KeyHold }, { sf::Keyboard::M });

    Bind UpCubeMove; UpCubeMove.KeyboardBind({ UpMoveTestObject }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Up });
    Bind DownCubeMove; DownCubeMove.KeyboardBind({ DownMoveTestObject }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Down });


    Bind LeftMove; LeftMove.KeyboardBind({LeftMoveCamera}, { EnumKeyStates::KeyHold }, { sf::Keyboard::A});
    Bind RightMove; RightMove.KeyboardBind({RightMoveCamera}, { EnumKeyStates::KeyHold }, { sf::Keyboard::D });

    Bind ForwardMove; ForwardMove.KeyboardBind({ ForwardMoveCamera }, { EnumKeyStates::KeyHold, EnumKeyStates::KeyHold }, { sf::Keyboard::W, sf::Keyboard::LShift });
    Bind BackwardMove; BackwardMove.KeyboardBind({ BackwardMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::S });

    Bind UpMove; UpMove.KeyboardBind({ UpMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::Q });
    Bind DownMove; DownMove.KeyboardBind({ DownMoveCamera }, { EnumKeyStates::KeyHold }, { sf::Keyboard::E });

    Bind CameraRot; CameraRot.MouseSensorBind({ CameraRotate }, EnumMouseSensorStates(MouseKeepMoved | MouseStartMoved));

    Bind CloseGameFirstMethod; CloseGameFirstMethod.KeyboardBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Keyboard::Escape });
    Bind CloseGameSecondMethod; CloseGameSecondMethod.MouseButtonsBind({ World::CloseGame }, { EnumKeyStates::KeyReleased }, { sf::Mouse::Left }, { sf::Event::EventType::Closed });

    InpSys->InsertBind(LeftCubeMove);
    InpSys->InsertBind(RightCubeMove);
    InpSys->InsertBind(ForwardCubeMove);
    InpSys->InsertBind(BackwardCubeMove);
    InpSys->InsertBind(UpCubeMove);
    InpSys->InsertBind(DownCubeMove);

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
    //obj.SetPosition(0, 0, -3);
    obj.AddRotation(0, 1.5, 0);

    obj.ApplyTransform();
}

void LeftMoveTestObject() {
    Cube1->AddPosition(0.1,0,0);
    Cube1->ApplyTransform();
}
void RightMoveTestObject() {
    Cube1->AddPosition(-0.1, 0, 0);
    Cube1->ApplyTransform();
}

void ForwardMoveTestObject() {
    Cube1->AddPosition(0, 0, 0.1);
    Cube1->ApplyTransform();
}
void BackwardMoveTestObject() {
    Cube1->AddPosition(0, 0, -0.1);
    Cube1->ApplyTransform();
}

void UpMoveTestObject() {
    Cube1->AddPosition(0, 0.1, 0);
    Cube1->ApplyTransform();
}
void DownMoveTestObject() {
    Cube1->AddPosition(0, -0.1, 0);
    Cube1->ApplyTransform();
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
        InpSys->IO_Events();
        Game->Update();

        CollisionPoints points;
        if (Collision::GJK((Collider*)Cube1->GetModuleByName("Collider"), (Collider*)Cube2->GetModuleByName("Collider"), points)) {
            Cube1->AddPosition(-(points.Normal.X * points.PenetrationDepth), -(points.Normal.Y * points.PenetrationDepth), -(points.Normal.Z * points.PenetrationDepth));
            Cube1->ApplyTransform();
        }

        render->RenderLoop(camera);
    }
}
