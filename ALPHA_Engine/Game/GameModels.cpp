#include "GameModels.h"
#include "Modules/Mesh.h"

//TODO: Function normilize color

inline void CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, Object *Obj) {
    Obj->AddPosition(Position);
    Obj->AddRotation(Rotation);
    Obj->SetScale(Scale);

    Mesh* mesh = new Mesh;
    Obj->AddModule(mesh);
}

inline Object* Primitives::Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Plane.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cube.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Circe.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Sphere.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cylinder.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cone.fbx");
    obj->ApplyTransform();

    return obj;
}

inline Object* Primitives::Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Torus.fbx");
    obj->ApplyTransform();

    return obj;
}