#pragma once
#include <vector>

#include "Core/Math/glmMath.h"
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
        void PrepareRender(const size_t width, const size_t height);
        void PrepareRender(
            glm::vec2 size,
            glm::vec2 position);

        ///Before use LoadMeshArray()
        void EntryPoint(std::vector<Core::SystemData*>& data) override;
        void RenderMeshes(Camera &camera, const MeshesBuffer &meshes);

        void GenerateVao(const Mesh &mesh);

        ///Check mesh valid
        [[nodiscard]] bool MeshChecker(const Mesh& mesh);

        [[nodiscard]] int GetRenderMode(const ShaderProgram& shader);

    public:
        RenderEngine(size_t order);
        ~RenderEngine() override = default;
    };
}
