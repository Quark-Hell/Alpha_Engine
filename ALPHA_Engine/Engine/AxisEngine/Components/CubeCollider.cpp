#include "CubeCollider.h"

#include "Rigidbody.h"

#include "Core/Logger/Logger.h"
#include "Core/World.h"

namespace AxisEngine {
    CubeCollider::CubeCollider(PhysicsEngine& engine) : Collider::Collider(engine) {
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
                AutoBuildColliderShape();
                _shape.reset(_physics->createShape(_boxGeometry, *_material));
                actor->attachShape(*_shape);
            }
        }
    }

    void CubeCollider::ResetShape() {
        _shape.reset(_physics->createShape(_boxGeometry, *_material));
    }

    void CubeCollider::AutoBuildColliderShape() {
        //TODO: Add auto build
        // 
        //if (auto oldRb = _parentObject->GetComponentByType<AxisEngine::>()) {
        //
        //}
        //
        //Core::Logger::LogWarning("Collider parent doesn't have mesh component " + __LOGERROR__);
    }
}