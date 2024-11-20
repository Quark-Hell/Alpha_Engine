#pragma once
#include <memory>
#include <string>

namespace Render::WindowsManager {
    class WindowsManager;
    class WindowsBuffer;
}

namespace Render::WindowsManager::BindsEngine {
    class InputSystem;
}

namespace Render::WindowsManager::AnomalyEngine {
    class RenderEngine;
    class Camera;
}

struct GLFWwindow;
struct GLFWmonitor;


namespace Render::WindowsManager {
    class Window {
        friend class WindowsManager;
        friend class AnomalyEngine::RenderEngine;
        friend class BindsEngine::InputSystem;
        friend class WindowsBuffer;

    private:
        GLFWwindow *_window;
        AnomalyEngine::Camera *_activeCamera = nullptr;

        int _width = 100;
        int _height = 100;

        std::string _title;

        bool _isSync = true;
        bool _isCursorVisible = true;


    public:
        Window() = delete;
        Window(int width, int height, const std::string& title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
        ~Window();

        void Resize(int width, int height);

        void SetSync(bool sync);
        void SetCamera(AnomalyEngine::Camera *camera);

        bool GetCursorVisible();
        void SetCursorVisible(bool isVisible);
    };
}
