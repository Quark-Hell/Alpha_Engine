#pragma once
#include "Core/Components/Component.h"

namespace AnomalyEngine::WindowsManager {
    class Window;
}
namespace Core {
    class Factory;
}

namespace AnomalyEngine::Render {
    class Camera : public Core::Component {
    friend class Core::Factory;

    private:
        explicit Camera(float fov = 90,float aspect = 1,float zNear = 0.1f,float zFar = 300);
        AnomalyEngine::WindowsManager::Window* _window = nullptr;

        float _fov = 90;
        float _aspect = 1;
        float _zNear = 0.1f;
        float _zFar = 300;

    public:
        ~Camera();
    };
}