#include "Collider.h"

#include "Rigidbody.h"
#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Systems/PhysicsEngine.h"

namespace AxisEngine {
    Collider::Collider(PhysicsEngine& engine) {
        _physics = engine.GetPhysics();

        _material.reset(_physics->createMaterial(0.5f, 0.5f, 0.6f));
    }

    void Collider::UpdateScale() {
        if (_parentObject == nullptr) {
            Core::Logger::LogError("Cannot update collides scale. Parent object is null", __LOGERROR__);
            return;
        }

        glm::vec3 scaleParent = _parentObject->transform.GetScale();

        auto equal = [](float a, float b) {
            return fabs(a - b) < 0.001f;
            };

        if (equal(scaleParent.x, _scale.x) &&   //Check if are equal
            equal(scaleParent.y, _scale.y) &&
            equal(scaleParent.z, _scale.z))
        {
            return;
        }

        _scale = physx::PxVec3(
            std::max(scaleParent.x, 0.0001f),
            std::max(scaleParent.y, 0.0001f),
            std::max(scaleParent.z, 0.0001f)
        );

        ResetShape();
    }
}