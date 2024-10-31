#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace Render::AnomalyEngine {
    class RenderEngine;
    namespace Components {
        class Camera;
    }
}

namespace Render::WindowsManager {

class Window {
    friend class Render::AnomalyEngine::RenderEngine;

     public:
        GLFWwindow* _window;
        Render::AnomalyEngine::Components::Camera* _activeCamera = nullptr;

        int _width = 100;
        int _height = 100;

        bool _isSync = true;
        bool _initialized = false;

        void Init();

     public:
        Window() = delete;
        Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
        ~Window() = default;

        void Resize(int width, int height);
        void SetSync(bool sync);

        void SetCamera(Render::AnomalyEngine::Components::Camera* camera);
};

}