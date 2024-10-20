#pragma once
#include <vector>
#include <memory>

namespace AnomalyEngine {
    namespace WindowsManager
    {
        class Window;
    }
    namespace Render
    {
        class Camera;
    }
}
namespace Core {
    class Host;
}

namespace AnomalyEngine::Render {
    class Render {
        friend class Core::Host;
    private:
        Render() = default;
        static Render* GetInstance();

        void ClearFrameBuffer();
        void PrepareRender();
        void SetActiveWindow(const AnomalyEngine::WindowsManager::Window* window);

        void SetWindowMatrix(int width, int height);
        void SetModelMatrix();

        //Orto or perspective
        //Before use SetWindowMatrix()
        void SetCameraProjection(const AnomalyEngine::WindowsManager::Window* window);
        void SetCameraTransform(AnomalyEngine::Render::Camera* camera);

        void RenderLoop(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows);
        void RenderScene(const AnomalyEngine::WindowsManager::Window* window);
    public:
        ~Render() = default;

    };
}
