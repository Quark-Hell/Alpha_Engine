#pragma once

#include <string>

#include "Collider.h"

namespace AxisEngine {
	class MeshCollider final : public AxisEngine::Collider {
		friend class CollidersBuffer;

	protected:
		MeshCollider(const std::string& linkToFBX);
		MeshCollider();

	public:
		~MeshCollider() override = default;

		bool Create(const std::string& linkToFBX);
		bool Create();

		void InitTransformatiom(Core::GameObject& newParent);
		void InitTransformatiom(Core::GameObject& oldParent, Core::GameObject& newParent);
	};
}