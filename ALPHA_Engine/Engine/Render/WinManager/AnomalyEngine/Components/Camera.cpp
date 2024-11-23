#include "Camera.h"
#include "Core/Logger/Logger.h"

namespace Render::WindowsManager::AnomalyEngine {
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
    glm::mat4x4 Camera::GetProjectionMatrix() {
        if (GetProjection()) {
            const glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(_fov), _aspect, _zNear, _zFar);
            return projectionMatrix;
        }
        else {
            //TODO: add support for ortho matrix
            //const glm::mat4 projectionMatrix = glm::ortho( 0, 400, 0, 400, _zNear, _zFar );
            Core::Logger::Logger::LogError("Now support only perspective matrix, returned identity matrix: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            const glm::mat4x4 projectionMatrix(1);
            return projectionMatrix;
        }
    }

    void Camera::SetFov(const float fov) {
        _fov = fov;
    }
    void Camera::SetAspect(const float aspect) {
        _aspect = aspect;
    }
    void Camera::SetZNear(const float zNear) {
        _zNear = zNear;
    }
    void Camera::SetZFar(const float zFar) {
        _zFar = zFar;
    }

    void Camera::GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar) {
        *Fov = Camera::_fov;
        *Aspect = Camera::_aspect;
        *ZNear = Camera::_zNear;
        *ZFar = Camera::_zFar;
    }
}