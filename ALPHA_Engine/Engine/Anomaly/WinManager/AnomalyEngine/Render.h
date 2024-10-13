#pragma once
#include <vector>
#include <memory>

namespace AnomalyEngine::WindowsManager {
    class Window;
}
namespace Core {
    class Host;
}

namespace AnomalyEngine::Render {
    class Render {
        friend class Core::Host;
    private:
        Render() = default;
        static Render& GetInstance();

        void ClearFrameBuffer();
        void PrepareRender();


        void RenderLoop(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows);
    public:
        ~Render() = default;

    };
}
