#include "Camera.h"

#include <glm/gtx/transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

#include "WindowsManager/Components/Window.h"

#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"

namespace AnomalyEngine {
    Camera::Camera(const size_t width, const size_t height, const float fov, const float aspect , const float zNear, const float zFar) {
        _width = width;
        _height = height;
        _fov = fov;
        _aspect = aspect;
        _zNear = zNear;
        _zFar = zFar;
    }

    void Camera::OnParentObjectChanged(Core::Object& newParent) {
        newParent.transform.IsCamera = true;
    }

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
        if (_window == nullptr) {
            Core::Logger::Logger::LogError("Windows was null, returned identity matrix " + __LOGERROR__);
            return glm::mat4x4(1);
        }

        if (GetProjection()) {
            if (_useRectangle) {
                if (_window->CheckRectangleExist(_rectangleIndex)) {
                    const glm::vec2 size = _window->GetRectangleSize(_rectangleIndex) * _window->GetSize();

                    const float aspect = size.x / size.y;
                    const glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(_fov), aspect, _zNear, _zFar);
                    return projectionMatrix;
                }
            }

            const glm::vec2 size = _window->GetSize();
            const glm::mat4x4 projectionMatrix = glm::perspectiveFov(glm::radians(_fov),size.x, size.y, _zNear, _zFar);
            return projectionMatrix;
        }
        else {
            //TODO: add support for ortho matrix
            //const glm::mat4 projectionMatrix = glm::ortho( 0, 400, 0, 400, _zNear, _zFar );
            Core::Logger::Logger::LogError("Now support only perspective matrix, returned identity matrix: " + __LOGERROR__);
            const glm::mat4x4 projectionMatrix(1);
            return projectionMatrix;
        }
    }

    void Camera::SetRenderWindow(WindowsManager::Window* window) {
        if (window == nullptr) {
            Core::Logger::LogError("Window is null: " + __LOGERROR__);
            return;
        }

        GLFWwindow* glfw = window->GetGLFWwindow();
        if (glfw == nullptr) {
            Core::Logger::LogError("GLFW window is null: " + __LOGERROR__);
            return;
        }

        _window = window;

        int width, height;
        glfwGetWindowSize(glfw, &width, &height);
        _width = width;
        _height = height;

        _aspect = width / static_cast<float>(height);
    }

    void Camera::SetFov(const float fov) {
        _fov = fov;
    }
    void Camera::SetZNear(const float zNear) {
        _zNear = zNear;
    }
    void Camera::SetZFar(const float zFar) {
        _zFar = zFar;
    }
    void Camera::SetWidth(const size_t width) {
        _width = width;
    }
    void Camera::SetHeight(const size_t height) {
        _height = height;
    }
    void Camera::SetUseRectangle(const bool use) {
        _useRectangle = use;
    }
    void Camera::SetIndexRectangle(const size_t index) {
        _rectangleIndex = index;
    }


    size_t Camera::GetWidth() const {
        return _width;
    }
    size_t Camera::GetHeight() const {
        return _height;
    }
    bool Camera::GetUseRectangle() const {
        return _useRectangle;
    }
    size_t Camera::GetRectangleIndex() const {
        return _rectangleIndex;
    }
}