#include "GameModels.h"
#include "Mesh.h"

//TODO: Function normilize color

inline void CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, Object *Obj) {
    Obj->AddPosition(Position);
    Obj->AddRotation(Rotation);
    Obj->AddScale(Scale);

    Mesh* mesh = new Mesh;
    Obj->AddModule(mesh);
}

inline Object* Primitives::Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Plane.fbx");

    return obj;
}

inline Object* Primitives::Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cube.fbx");

    return obj;
}

inline Object* Primitives::Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Circe.fbx");

    return obj;
}

inline Object* Primitives::Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Sphere.fbx");

    return obj;
}

inline Object* Primitives::Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cylinder.fbx");

    return obj;
}

inline Object* Primitives::Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cone.fbx");

    return obj;
}

inline Object* Primitives::Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Object* obj = new Object;
    CreateObject(Position, Rotation, Scale, obj);

    ((Mesh*)obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Torus.fbx");

    return obj;
}