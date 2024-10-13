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
        Camera();
        AnomalyEngine::WindowsManager::Window* _window = nullptr;

    public:
        ~Camera();

        bool AttachWindow(AnomalyEngine::WindowsManager::Window* window);
    };
}