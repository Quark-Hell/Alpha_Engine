#pragma once

#include "Core/Resources/Geometry.h"
#include "Core/Objects/GameObject.h"
#include "Core/Math/glmMath.h"

#if _DEBUG && ANOMALY_ENGINE_INCLUDED
#include "Core/Objects/FakeObject.h"

namespace AnomalyEngine {
	class Mesh;
}
#endif // _DEBUG

namespace AxisEngine {
	class AABB {
		friend class PhysicsEngine;
		friend class AABBBuffer;

	private:
		Core::Geometry* _geometry;

		glm::vec3 _position;
		glm::vec3 _scale{ 0,0,0 };

#if _DEBUG && ANOMALY_ENGINE_INCLUDED
	private:
		Core::FakeObject& _fakeObject;
		AnomalyEngine::Mesh* _mesh;
#endif // _DEBUG

	protected:
		AABB();
		void CreateAABB();

	public:
		~AABB() = default;

		void UpdateAABB(Core::GameObject& parentObject);
		void UpdateAABB(float radius);

	};
}