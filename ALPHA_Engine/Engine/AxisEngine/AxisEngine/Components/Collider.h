#pragma once

#include "Core/Components/Component.h"
#include "Core/Resources/Geometry.h"

#include "AxisEngine/External/PhysX/PxPhysicsAPI.h"

namespace AxisEngine {
	struct PxMaterialDeleter {
		void operator()(physx::PxMaterial* s) const noexcept {
			if (s) s->release();
		}
	};
	struct PxShapeDeleter {
		void operator()(physx::PxShape* s) const noexcept {
			if (s) s->release();
		}
	};
}

namespace AxisEngine {
	class AABB;

	class Collider : public Core::Component {
		friend class PhysicsEngine;
		friend class CollidersBuffer;
		friend class RigidBody;

	protected:
		physx::PxPhysics* _physics = nullptr;

		std::unique_ptr<physx::PxMaterial, PxMaterialDeleter> _material;
		std::unique_ptr<physx::PxShape, PxShapeDeleter> _shape;

		physx::PxVec3 _scale = { 1.0, 1.0, 1.0f };

	protected:
		Collider(PhysicsEngine& engine);
		
		//Typically used for change ridgidbody for this collider
		virtual void ResetShape() = 0;
		void UpdateScale();

	public:
		virtual ~Collider() override = default;
	};
}