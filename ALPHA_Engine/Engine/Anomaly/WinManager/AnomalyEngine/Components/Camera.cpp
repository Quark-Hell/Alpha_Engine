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

    void Camera::SetProjection(const bool isPerspective) {
        if (isPerspective)
            _isPerspective = true;
        else
            _isPerspective = false;
    }
    bool Camera::GetProjection() const {
        return _isPerspective;
    }

    void Camera::GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar) {
        *Fov = Camera::_fov;
        *Aspect = Camera::_aspect;
        *ZNear = Camera::_zNear;
        *ZFar = Camera::_zFar;
    }
}