#pragma once

#include "Core/Math/glmMath.h"

namespace AxisEngine {
    class Plane
    {
    public:
        glm::vec3 P1;
        glm::vec3 Normal;

    public:
        inline Plane(glm::vec3 p1, glm::vec3 normal) {
            P1 = p1;
            Normal = normal;
        }
    };
}