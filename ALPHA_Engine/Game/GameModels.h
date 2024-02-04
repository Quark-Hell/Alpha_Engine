#pragma once

#include "Basical_Type.h"

#include "Object.h"
#include "Modules/Mesh.h"

//Todo: move this class into "Primitives" class into Engine folder

class Primitives {
public: 
	static std::shared_ptr<Object> Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	static std::shared_ptr<Object> Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale);

private:
	static void CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, std::shared_ptr<Object> Obj);
};