#include "Camera.h"

namespace AnomalyEngine::Render {
    Camera::Camera() = default;
    Camera::~Camera() = default;

    bool Camera::AttachWindow(AnomalyEngine::WindowsManager::Window *window) {
        if (window == nullptr)
            return false;

        _window = window;
        return true;
    }

}