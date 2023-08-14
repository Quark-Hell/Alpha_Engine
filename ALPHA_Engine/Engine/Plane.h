#pragma once
#include "Basical_Type.h"
#include "Vectors.h"

class Plane
{
public:
    Vector3 P1;
    Vector3 Normal;

public:
    inline Plane(Vector3 p1, Vector3 normal) {
        P1 = p1;
        Normal = normal;
    }
};