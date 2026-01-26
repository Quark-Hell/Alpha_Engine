#include "CubeCollider.h"

#include "Rigidbody.h"

#include "Core/Logger/Logger.h"
#include "Core/World.h"

namespace AxisEngine {
    CubeCollider::CubeCollider() {
        _shape.reset(_physics->createShape(_boxGeometry, *_material));
    }

    void CubeCollider::UpdateParentObject(Core::Object& newParent) {
        {
            if (auto oldParent = GetParentObject()) {
                if (auto oldRb = oldParent->GetComponentByType<AxisEngine::RigidBody>()) {
                    if (auto actor = oldRb->GetRigidActor()) {
                        actor->detachShape(*_shape.get());
                        _shape->release();
                    }
                }
            }       
        }

        auto rb = newParent.GetComponentByType<AxisEngine::RigidBody>();

        if (rb != nullptr) {
            auto actor = rb->GetRigidActor();
            if (actor != nullptr) {
                //TODO: add multi-colliders support (local position)
                // _boxShape->setLocalPose(PxTransform(PxVec3(1.0f, 0, 0)));
                _shape.reset(_physics->createShape(_boxGeometry, *_material));
                actor->attachShape(*_shape);
            }
        }
    }
}