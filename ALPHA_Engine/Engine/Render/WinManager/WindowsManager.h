#pragma once

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
        WindowsManager();
        static WindowsManager* GetInstance();
        void Init();

     public:
        ~WindowsManager();
};

}
