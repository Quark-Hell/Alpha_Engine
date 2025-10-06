#include "DirectLightsBuffer.h"

namespace AnomalyEngine {
    DirectLightsBuffer::DirectLightsBuffer(size_t initialBufferSize) : TSystemData("DirectLightsBuffer", initialBufferSize) {}

    DirectLight& DirectLightsBuffer::CreateDirectLight(const glm::vec3& direction) {
        _data.emplace_back(std::unique_ptr<DirectLight>(new DirectLight(direction)));
        return *_data.back().get();
    }
}
