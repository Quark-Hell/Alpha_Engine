#include "CamerasBuffer.h"

namespace AnomalyEngine {
    CamerasBuffer::CamerasBuffer() : TSystemData("CamerasBuffer") {};

    Camera* CamerasBuffer::CreateCamera(const size_t width, const size_t height, const float fov, const float aspect, const float zNear, const float zFar) {
        _data.emplace_back(std::unique_ptr<Camera>(new Camera(width, height, fov, aspect, zNear, zFar)));

        return _data.back().get();
    }
}