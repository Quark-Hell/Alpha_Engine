#pragma once
#include <vector>
#include <memory>

#include "Core/Math/glmMath.h"
#include "Core/ECS/System.h"

#include "Utility/BasicShapes/Shape.h"

namespace WindowsManager {
    class Window;
}

namespace AnomalyEngine {
    class MeshesBuffer;
    class TempMeshesBuffer;
    class ShaderProgram;
    class Camera;
    class Mesh;
}

namespace AnomalyEngine  {
    template<typename T>
    concept MeshBufferLike = requires(T t) {
            requires std::derived_from<
                typename std::remove_pointer_t<
                    typename std::pointer_traits<
                        typename std::remove_cvref_t<
                            decltype(t.GetAllData()[0])
                        >
                    >::element_type
                >,
                AnomalyEngine::Mesh
            >;
    };

    class RenderEngine final : public Core::System {
    private:
        //Temp data
        unsigned int _vao = 0;
        std::vector<std::shared_ptr<Shape>> _shapesBuffer;

    private:
        void ClearFrameBuffer();
        void PrepareRender(const size_t width, const size_t height);
        void PrepareRender(
            glm::vec2 size,
            glm::vec2 position);

        ///Before use LoadMeshArray()
        void EntryPoint(std::vector<Core::SystemData*>& data) override;
        void InitTempBuffer();
        bool _isNotInited = false;

        template<MeshBufferLike T>
        void RenderMeshes(Camera& camera, const T& meshes) {
            for (auto& mesh : meshes._data) {
                if (!MeshChecker(*mesh))
                    continue;

                auto parent = mesh->GetParentObject();
                if (parent == nullptr)
                    continue;

                auto geometry = mesh->GetGeometry();

                GenerateVao(*mesh);

                glUseProgram(mesh->_material.Shader->GetProgramId());
                glBindVertexArray(_vao);

                const int renderMode = GetRenderMode(*mesh->_material.Shader);

                mesh->_material.Shader->ApplyShadersSettings(camera);

                if (geometry->IsIndexed)
                    glDrawElements(renderMode, geometry->Indices->size(), GL_UNSIGNED_INT, geometry->Indices->data());
                else
                    glDrawArrays(renderMode, 0, geometry->Vertices->size() / 3);

                //glDepthFunc(GL_NEVER);
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);

                //Delete vao that was created by GenerateVao() function
                glDeleteVertexArrays(1, &_vao);
            }
        }

        void GenerateVao(const Mesh &mesh);

        ///Check mesh valid
        [[nodiscard]] bool MeshChecker(const Mesh& mesh);

        [[nodiscard]] int GetRenderMode(const ShaderProgram& shader);

    public:
        RenderEngine(size_t order);
        ~RenderEngine() override = default;
    };
}
