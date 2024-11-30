#include "DirectLightsBuffer.h"

namespace AnomalyEngine {
    DirectLightsBuffer::DirectLightsBuffer() : TSystemData("DirectLightsBuffer") {
        _data.reserve(16);
    }

    DirectLight& DirectLightsBuffer::CreateDirectLight(const Core::Vector3& direction) {
        _data.emplace_back(std::unique_ptr<DirectLight>(new DirectLight(direction)));
        return *_data.back().get();
    }
}
