#pragma once
#include <vector>
#include <memory>

namespace Core {
    class Host;
}

namespace Render::WindowsManager {
    class Window;

    class WindowsManager {
        friend class Core::Host;

    private:
        WindowsManager();

        static WindowsManager *GetInstance();

        void Init();

        void RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>> *windows);

    public:
        ~WindowsManager();
    };
}
