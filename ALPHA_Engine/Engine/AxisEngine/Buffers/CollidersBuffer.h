#pragma once

#include "AxisEngine/Components/Collider.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class CollidersBuffer final : public Core::TSystemData<Collider> {
        friend class PhysicsEngine;

    public:
        CollidersBuffer();
        ~CollidersBuffer() override = default;

        Collider& CreateCollider();
    };
}

