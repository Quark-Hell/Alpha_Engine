#pragma once

#include "Collider.h"

namespace AxisEngine {
	class MeshCollider final : public AxisEngine::Collider {
		friend class CollidersBuffer;

	protected:
		MeshCollider() = default;

	public:
		~MeshCollider() override = default;
	};
}