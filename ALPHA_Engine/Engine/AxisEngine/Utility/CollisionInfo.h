#pragma once

#include "Core/Math/glmMath.h"

#include <vector>

namespace AxisEngine {
	class CollisionInfo {
	public:
		glm::vec3 Normal;
		float PenetrationDepth;
		std::vector<glm::vec3> CollisionPoints;
	};
}