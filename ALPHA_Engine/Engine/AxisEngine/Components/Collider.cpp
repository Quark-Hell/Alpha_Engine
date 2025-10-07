#include "Collider.h"

#include "Rigidbody.h"

#include "Core/Factory.h"

namespace AxisEngine {
    Collider::Collider() : _fakeObject(Core::Factory::CreateFakeObject()) {
        
    }

    void Collider::UpdateParentObject(Core::Object& newParent) {
        auto rb = newParent.GetComponentByType<AxisEngine::RigidBody>();

        if (rb != nullptr) {
            rb->UpdateCenterMass();
        }
    }

    void Collider::InitCollider(bool isExpand) {

    }
}