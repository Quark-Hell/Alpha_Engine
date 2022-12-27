#pragma once

#include "Basical_Type.h"

class Primitives {
public:
	 static inline Object* Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Sphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static inline Object* Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
};