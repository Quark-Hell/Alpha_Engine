#pragma once

#include "AxisEngine/Components/Collider.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class CollidersBuffer final : public Core::TSystemData<Collider> {
        friend class PhysicsEngine;

    public:
        CollidersBuffer(size_t initialBufferSize = 0);
        ~CollidersBuffer() override = default;

        Collider& CreateCollider();
    };
}

