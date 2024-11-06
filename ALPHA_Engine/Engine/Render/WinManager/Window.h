#pragma once
#include <memory>

namespace Render::WindowsManager {
    class WindowsManager;
}

namespace Render::WindowsManager::BindsEngine {
    class InputSystem;
}

namespace Render::AnomalyEngine {
    class RenderEngine;
    namespace Components {
        class Camera;
    }
}

namespace Core {
    class Factory;
}

struct GLFWwindow;
struct GLFWmonitor;


namespace Render::WindowsManager {

class Window {
    friend class Render::WindowsManager::WindowsManager;
    friend class Render::AnomalyEngine::RenderEngine;
    friend class Render::WindowsManager::BindsEngine::InputSystem;
    friend class Core::Factory;

    private:
        GLFWwindow* _window;
        Render::AnomalyEngine::Components::Camera* _activeCamera = nullptr;

     public:
        int _width = 100;
        int _height = 100;

        bool _isSync = true;
        bool _initialized = false;

        void Init();

     public:
        Window() = delete;
        Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
        ~Window();

        void Resize(int width, int height);
        void SetSync(bool sync);

        void SetCamera(Render::AnomalyEngine::Components::Camera* camera);
};

}