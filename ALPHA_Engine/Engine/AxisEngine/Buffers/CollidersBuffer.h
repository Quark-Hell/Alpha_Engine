#pragma once

#include "AxisEngine/Components/Collider.h"
#include "Core/ECS/TSystemData.h"

namespace AxisEngine {
    class CollidersBuffer final : public Core::TSystemData<Collider> {
        friend class PhysicsEngine;
        friend class CollisionEngine;

    public:
        CollidersBuffer(size_t initialBufferSize = 0);
        ~CollidersBuffer() override = default;

        template <typename T>
        requires std::is_base_of_v<Collider, T> && !std::is_same_v<Collider, T>
        T& CreateCollider() {
            _data.emplace_back(std::unique_ptr<T>(new T()));

            return *static_cast<T*>(_data.back().get());
        }
    };
}

