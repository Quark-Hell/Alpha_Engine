#pragma once

#include "Collider.h"

namespace AxisEngine {
	class CubeCollider final : public AxisEngine::Collider {
	private:
		physx::PxBoxGeometry _boxGeometry{ physx::PxVec3(1.0f, 1.0f, 1.0f) };

	protected:
		CubeCollider();

		void virtual UpdateParentObject(Core::Object& newParent) override;
	};

}