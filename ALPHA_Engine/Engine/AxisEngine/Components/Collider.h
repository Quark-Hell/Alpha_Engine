#pragma once

#include "Core/Objects/FakeObject.h"
#include "Core/Components/Geometry.h"
#include "AABB.h"

namespace AxisEngine {
	class Collider : public Core::Geometry {
		friend class PhysicsEngine;
		friend class CollidersBuffer;

	protected:
		Core::FakeObject& _fakeObject;
		AABB* _AABB;

	private:
		void UpdateParentObject(Core::Object& newParent) override;

	protected:
		Collider();
		virtual void InitCollider(bool isExpand = true);

	public:
		virtual ~Collider() override = default;
	};
}