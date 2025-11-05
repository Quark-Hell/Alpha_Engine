#pragma once

#include <vector>

#include "Core/ECS/System.h"
#include "Core/Math/glmMath.h"

#include "AxisEngine/Components/Collider.h"

#include "AxisEngine/Utility/CollisionInfo.h"
#include "AxisEngine/Utility/Simplex.h"
#include "AxisEngine/Utility/Plane.h"

namespace AxisEngine {
	class CollisionEngine final : public Core::System {
	public:
		const unsigned int GJKaccurate = 100;
		const unsigned int EPAaccurate = 100;

	private:
		//bool BoxToBox(BoxCollider& colliderA, BoxCollider& colliderB);
		//bool SphereToSphere(Geometry& colliderA, Geometry& colliderB);
		//bool SphereToBox(Geometry& colliderA, Geometry& colliderB);

		void EntryPoint(std::vector<Core::SystemData*>& data) override;

		glm::vec3 Support(const Collider& colliderA, const Collider& colliderB, glm::vec3 direction);
		bool GJK(Collider& colliderA, Collider& colliderB);
		bool EPA(Simplex& simplex, const Collider& colliderA, const Collider& ColliderB, CollisionInfo& colInfo);

		std::pair<std::vector<glm::vec4>, size_t> GetFaceNormals(std::vector<glm::vec3>& polytope, std::vector<size_t>& faces);
		void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b);

		void CalculateContactPoints(Collider& contactObject1, Collider& contactObject2, CollisionInfo& colInfo);
		void CheckIntersection(
			const std::vector<std::pair<glm::vec3, float>>& contactPointsA,
			const std::vector<std::pair<glm::vec3, float>>& contactPointsB,
			glm::vec3 normal,
			std::vector<glm::vec3>& contactPointsBuf);

	public:
		CollisionEngine(size_t order);
		~CollisionEngine() override = default;
	};
}