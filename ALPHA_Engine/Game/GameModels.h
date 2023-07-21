#pragma once

#include "Basical_Type.h"

#include "Object.h"
#include "Modules/Mesh.h"

class Primitives {
public: 
	static Object* Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static Object* Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

private:
	static void CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, Object* Obj);
};