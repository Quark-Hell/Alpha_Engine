#include "Camera.h"

namespace AnomalyEngine::Render {
    Camera::Camera(const float fov, const float aspect , const float zNear, const float zFar)
    {
        _fov = fov;
        _aspect = aspect;
        _zNear = zNear;
        _zFar = zFar;
    }
    Camera::~Camera() = default;
}