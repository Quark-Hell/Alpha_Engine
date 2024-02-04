#include "GameModels.h"


//TODO: Function normilize color

void Primitives::CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, std::shared_ptr<Object> Obj) {
    Obj->AddPosition(Position);
    Obj->AddRotation(Rotation);
    Obj->SetScale(Scale);
    
    std::shared_ptr<Module> mesh = std::make_shared<Mesh>();
    Obj->AddModule(std::dynamic_pointer_cast<Module>(mesh));
}

std::shared_ptr<Object> Primitives::Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);
    
    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Plane.fbx");
    obj->ApplyTransformation();
    
    return obj;
}

std::shared_ptr<Object> Primitives::Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
   std::shared_ptr<Object> obj = std::make_shared<Object>();
   CreateObject(Position, Rotation, Scale, obj);

   std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cube.fbx");
   obj->ApplyTransformation();
   
   return obj;
}

std::shared_ptr<Object> Primitives::Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);

    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Circe.fbx");
    obj->ApplyTransformation();

    return obj;
}

std::shared_ptr<Object> Primitives::Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);
    
    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Sphere.fbx");
    obj->ApplyTransformation();
    
    return obj;
}

std::shared_ptr<Object> Primitives::Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);
    
    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cylinder.fbx");
    obj->ApplyTransformation();
    
    return obj;
}

std::shared_ptr<Object> Primitives::Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);
    
    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Cone.fbx");
    obj->ApplyTransformation();
    
    return obj;
}

std::shared_ptr<Object> Primitives::Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    CreateObject(Position, Rotation, Scale, obj);
    
    std::dynamic_pointer_cast<Mesh>(obj->GetModuleByIndex(0))->Create("\\Models\\Primitives\\Torus.fbx");
    obj->ApplyTransformation();
    
    return obj;
}