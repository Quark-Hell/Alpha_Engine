#pragma once

#include "AxisEngine/Components/RigidBody.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class RigidBodiesBuffer final : public Core::TSystemData<RigidBody> {
        friend class PhysicsEngine;
        friend class CollisionEngine;

    public:
        RigidBodiesBuffer(size_t initialBufferSize = 0);
        ~RigidBodiesBuffer() override = default;

        RigidBody& CreateRigidBody(PhysicsEngine& engine);
    };
}

