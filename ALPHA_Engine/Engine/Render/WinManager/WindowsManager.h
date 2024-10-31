#pragma once
#include "Window.h"

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

     public:
        ~WindowsManager();
};

}
