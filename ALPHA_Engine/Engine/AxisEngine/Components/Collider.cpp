#include "Collider.h"

#include "Rigidbody.h"

#include "Core/Objects/FakeObject.h"
#include "Core/Factory.h"

namespace AxisEngine {
    Collider::Collider() : _fakeObject(Core::Factory::CreateObject<Core::FakeObject>()) {
        
    }

    void Collider::UpdateParentObject(Core::Object& newParent) {
        auto rb = newParent.GetComponentByType<AxisEngine::RigidBody>();

        if (rb != nullptr) {
            rb->UpdateCenterMass();
        }
    }

    void Collider::Create(Core::Geometry& geometry) {
        geometry.MakeUnique();

        _geometry = &geometry;
    }

    const Core::Geometry* Collider::GetGeometry() const noexcept {
        return _geometry;
    }
}