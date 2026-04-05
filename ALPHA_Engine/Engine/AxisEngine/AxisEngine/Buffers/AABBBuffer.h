#pragma once

#include "AxisEngine/Components/AABB.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class AABBBuffer final : public Core::TSystemData<AABB> {
        friend class PhysicsEngine;

    public:
        AABBBuffer(size_t initialBufferSize = 0);
        ~AABBBuffer() override = default;

        AABB& CreateAABB();
    };
}