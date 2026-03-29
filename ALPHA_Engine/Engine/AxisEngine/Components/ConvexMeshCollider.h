#pragma once

#include "Collider.h"

namespace AxisEngine {
	struct PxConvexMeshDeleter {
		void operator()(physx::PxConvexMesh* s) const noexcept {
			if (s) s->release();
		}
	};
}

namespace AxisEngine {
	class ConvexMeshCollider final : public AxisEngine::Collider {
		friend class CollidersBuffer;

	private:
		std::unique_ptr <physx::PxConvexMesh, PxConvexMeshDeleter> _convexMesh = nullptr;

	protected:
		ConvexMeshCollider(PhysicsEngine& engine);

	public:
		~ConvexMeshCollider() override = default;

		void LoadGeometry(Core::Geometry& geometry);

		void virtual OnParentObjectChanged(Core::Object& newParent) override;
		void virtual ResetShape() override;
	};
}