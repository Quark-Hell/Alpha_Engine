#pragma once

#include "AxisEngine/Components/RigidBody.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class RigidBodiesBuffer final : public Core::TSystemData<RigidBody> {
        friend class PhysicsEngine;

    public:
        RigidBodiesBuffer();
        ~RigidBodiesBuffer() override = default;

        RigidBody& CreateRigidBody();
    };
}

