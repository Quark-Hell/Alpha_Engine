#pragma once

#include "Basical_Type.h"

class Primitive {
public:
	static void Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void UVSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void IcoSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);

public:
	static void Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color);
};