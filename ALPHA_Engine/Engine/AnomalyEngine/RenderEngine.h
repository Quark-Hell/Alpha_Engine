#pragma once
#include <vector>
#include "Core/ECS/System.h"

namespace WindowsManager {
    class Window;
}

namespace AnomalyEngine {
    class MeshesBuffer;
    class ShaderProgram;
    class Camera;
    class Mesh;
}

namespace AnomalyEngine  {
    class RenderEngine final : public Core::System {
    private:
        //Temp data
        unsigned int _vao = 0;

    private:
        void ClearFrameBuffer();
        void PrepareRender();

        void SetWindowMatrix(size_t width, size_t height);

        ///Before use LoadMeshArray()
        void EntryPoint(std::vector<Core::SystemData*>& data) override;
        void RenderMeshes(Camera &camera, const MeshesBuffer &meshes);

        void GenerateVao(const Mesh &mesh);

        ///Check mesh valid
        [[nodiscard]] bool MeshChecker(const Mesh& mesh);

        [[nodiscard]] int GetRenderMode(const ShaderProgram& shader);

    public:
        RenderEngine();
        ~RenderEngine() override = default;
    };
}
