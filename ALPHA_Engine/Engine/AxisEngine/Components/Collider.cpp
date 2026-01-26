#include "Collider.h"

#include "Rigidbody.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Systems/PhysicsEngine.h"

namespace AxisEngine {
    Collider::Collider(PhysicsEngine& engine) {
        _physics = engine.GetPhysics();

        if (_physics == nullptr) {
            Core::Logger::LogCritical("Collider cannot be intialized, because engine doesn't conain physics module " + __LOGERROR__);
        }

        _material.reset(_physics->createMaterial(0.5f, 0.5f, 0.6f));
    }

    //void Collider::Create(Core::Geometry& geometry) {
    //    geometry.MakeUnique();
    //
    //    _geometry = &geometry;
    //}
    //
    //const Core::Geometry* Collider::GetGeometry() const noexcept {
    //    return _geometry;
    //}
}