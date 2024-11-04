#pragma once
#include <vector>
#include <memory>

namespace Render {
    namespace WindowsManager {
        class Window;
        class WindowsManager;
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

    enum RenderModes : unsigned short {
        Points = 0,
        LineStrip = 1,
        LineLoop = 2,
        Lines = 3,
        LineStripAdjacency = 4,
        LinesAdjacency = 5,
        TriangleStrip = 6,
        TriangleFan = 7,
        Triangles = 8,
        TriangleStripAdjacency = 9,
        TrianglesAdjacency = 10,
        Patches = 11,
    };

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
    public:
        ~RenderEngine() = default;

    };
}
