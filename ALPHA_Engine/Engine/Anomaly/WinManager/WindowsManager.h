#pragma once
#include <cstdint>

namespace AnomalyEngine::Render {
    class Render;
}

namespace Core {
    class Host;
    class Factory;
}

namespace AnomalyEngine::WindowsManager {

class Window;

class WindowsManager {
    friend class AnomalyEngine::Render::Render;
    friend class Core::Host;
    friend class Core::Factory;

    private:
      bool _initialized = false;

      WindowsManager();
      static WindowsManager& GetInstance();

     public:
       ~WindowsManager();
};

}
