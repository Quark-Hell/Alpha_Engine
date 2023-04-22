#pragma once

#include "Basical_Type.h"

#include "Object.h"
#include "Modules/Mesh.h"

class Primitives {
public: 
	static inline Object* Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
	static inline Object* Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

private:
	static inline void CreateObject(Vector3 Position, Vector3 Rotation, Vector3 Scale, Object* Obj);
};