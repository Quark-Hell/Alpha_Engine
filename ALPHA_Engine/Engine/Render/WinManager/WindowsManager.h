#pragma once
#include "Window.h"
#include <vector>
#include <memory>

namespace Render::AnomalyEngine {
    class RenderEngine;
}

namespace Core {
    class Host;
    class Factory;
}

namespace Render::WindowsManager {

class WindowsManager {
    friend class AnomalyEngine::RenderEngine;
    friend class Core::Host;
    friend class Core::Factory;

    private:
        WindowsManager();
        static WindowsManager* GetInstance();
        void Init();

        void RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows);

     public:
        ~WindowsManager();
};

}
