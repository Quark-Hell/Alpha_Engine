#pragma once

#include "Collider.h"

namespace AxisEngine {
	class CubeCollider final : public AxisEngine::Collider {
		friend class PhysicsEngine;
		friend class CollidersBuffer;
		friend class RigidBody;

	protected:
		CubeCollider(PhysicsEngine& engine);

		void virtual OnParentObjectChanged(Core::Object& newParent) override;
		void virtual ResetShape() override;
	};

}