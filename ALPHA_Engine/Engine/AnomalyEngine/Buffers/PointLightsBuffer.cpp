#include "PointLightsBuffer.h"

namespace AnomalyEngine {
    PointLightsBuffer::PointLightsBuffer() : TSystemData("PointLightsBuffer") {
        _data.reserve(16);
    }

    PointLight* PointLightsBuffer::CreatePointLight(const float radius, const float constant, const float linear, const float quadratic) {
        _data.emplace_back(std::unique_ptr<PointLight>(new PointLight(radius, constant, linear, quadratic)));
        return _data.back().get();
    }
}
