#pragma once

#include "Collider.h"

namespace AxisEngine {
	class CubeCollider final : public AxisEngine::Collider {
		friend class PhysicsEngine;
		friend class CollidersBuffer;
		friend class RigidBody;

	private:
		physx::PxBoxGeometry _boxGeometry{ physx::PxVec3(1.0f, 1.0f, 1.0f) };

	protected:
		CubeCollider(PhysicsEngine& engine);

		void virtual UpdateParentObject(Core::Object& newParent) override;
		void virtual ResetShape() override;
		void virtual AutoBuildColliderShape() override;
	};

}