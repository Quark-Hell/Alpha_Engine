#include "CollidersBuffer.h"

namespace AxisEngine {
    CollidersBuffer::CollidersBuffer() : TSystemData("CollidersBuffer") {
        _data.reserve(16);
    }

    Collider& CollidersBuffer::CreateCollider() {
        _data.emplace_back(std::unique_ptr<Collider>(new Collider()));

        return *_data.back().get();
    }
}