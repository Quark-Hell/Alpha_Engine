#pragma once
#include <list>
#include <vector>
#include <memory>


namespace Render::WindowsManager {
    class Window;
    class WindowsManager;

    namespace AnomalyEngine {
        class ShaderProgram;
    }

    namespace AnomalyEngine {
        class Camera;
        class Mesh;
    }
}


namespace Core {
    class Geometry;
    class Host;
    class Component;
}

namespace Render::WindowsManager::AnomalyEngine {

    class RenderEngine {
        friend class Core::Host;
        friend class Render::WindowsManager::WindowsManager;
    private:
        RenderEngine() = default;
        static RenderEngine* GetInstance();

        void ClearFrameBuffer();
        void PrepareRender();

        void SetWindowMatrix(int width, int height);

        ///Always set to null after end of cycle
        std::vector<std::unique_ptr<Core::Component>>* _meshBuffer;
        void LoadMeshArray(std::vector<std::unique_ptr<Core::Component>>* meshBuffer);

        ///Before use LoadMeshArray()
        void RenderLoop(Render::WindowsManager::Window& windows);
        void RenderScene(const Render::WindowsManager::Window& window);
        void RenderMeshes(Render::WindowsManager::AnomalyEngine::Camera* camera);

        void GenerateVao(Render::WindowsManager::AnomalyEngine::Mesh *mesh);

        ///Check mesh valid
        [[nodiscard]] bool MeshChecker(const Render::WindowsManager::AnomalyEngine::Mesh* mesh);

        [[nodiscard]] int GetRenderMode(Render::WindowsManager::AnomalyEngine::ShaderProgram& shader);
    public:
        ~RenderEngine() = default;

    };
}
