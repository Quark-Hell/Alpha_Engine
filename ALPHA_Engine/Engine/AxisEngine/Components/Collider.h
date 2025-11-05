#pragma once

#include "Core/Components/Component.h"
#include "Core/Resources/Geometry.h"

namespace AxisEngine {
	class AABB;

	class Collider : public Core::Component {
		friend class PhysicsEngine;
		friend class CollidersBuffer;

	protected:
		Core::FakeObject& _fakeObject;
		AABB* _AABB = nullptr;

		Core::Geometry* _geometry;

	protected:
		Collider();

		void virtual UpdateParentObject(Core::Object& newParent) override;

	public:
		virtual ~Collider() override = default;

		void Create(Core::Geometry& geometry);
		[[nodiscard]] const Core::Geometry* GetGeometry() const noexcept;
	};
}