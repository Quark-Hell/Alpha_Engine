#include "AABBBuffer.h"

namespace AxisEngine {
    AABBBuffer::AABBBuffer(size_t initialBufferSize) : TSystemData("AABBBuffer", initialBufferSize) {}

    AABB& AABBBuffer::CreateAABB() {
        _data.emplace_back(std::unique_ptr<AABB>(new AABB()));

        return *_data.back().get();
    }
}