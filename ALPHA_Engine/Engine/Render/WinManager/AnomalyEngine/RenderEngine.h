#pragma once
#include <vector>
#include <memory>

namespace Render {
    namespace WindowsManager {
        class Window;
        class WindowsManager;
    }

    namespace AnomalyEngine::Shaders {
        class ShaderProgram;
    }

    namespace AnomalyEngine::Components {
        class Camera;
        class Mesh;
    }
}

namespace Core {
    class Host;
}

namespace Render::AnomalyEngine {

    class RenderEngine {
        friend class Core::Host;
        friend class Render::WindowsManager::WindowsManager;
    private:
        RenderEngine() = default;
        static RenderEngine* GetInstance();

        void ClearFrameBuffer();
        void PrepareRender();

        void SetWindowMatrix(int width, int height);
        void SetModelMatrix();

        ///Orto or perspective
        ///
        ///Before use SetWindowMatrix()
        void SetCameraProjection(const Render::WindowsManager::Window& window);
        void SetCameraTransform(Render::AnomalyEngine::Components::Camera* camera);

        ///Always set to null after end of cycle
        std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* _meshBuffer;
        void LoadMeshArray(std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* meshBuffer);

        ///Before use LoadMeshArray()
        void RenderLoop(Render::WindowsManager::Window& windows);
        void RenderScene(const Render::WindowsManager::Window& window);
        void RenderMeshes(Render::AnomalyEngine::Components::Camera* camera);

        void GenerateVao(Render::AnomalyEngine::Components::Mesh *mesh);

        ///Check mesh valid
        [[nodiscard]] bool MeshChecker(const Render::AnomalyEngine::Components::Mesh* mesh);

        [[nodiscard]] int GetRenderMode(Render::AnomalyEngine::Shaders::ShaderProgram& shader);
    public:
        ~RenderEngine() = default;

    };
}
