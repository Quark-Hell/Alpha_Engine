#include "CubeCollider.h"

#include "Rigidbody.h"

#include "Core/Logger/Logger.h"
#include "Core/World.h"

namespace AxisEngine {
    CubeCollider::CubeCollider(PhysicsEngine& engine) : Collider::Collider(engine) {
        ResetShape();
    }

    void CubeCollider::OnParentObjectChanged(Core::Object& newParent) {
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
                ResetShape();
                actor->attachShape(*_shape);
            }
        }
    }

    void CubeCollider::ResetShape() {
        if (_material == nullptr) {
            Core::Logger::LogError("Cannot reset shape. Material is null", __LOGERROR__);
            return;
        }

        physx::PxBoxGeometry geom(_scale);

        if (_shape) {
            _shape->setGeometry(geom);
        }
        else {
            _shape.reset(_physics->createShape(geom, *_material, true));
        }
    }
}