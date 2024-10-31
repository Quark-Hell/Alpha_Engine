#pragma once
#include <memory>
#include <Render/WinManager/AnomalyEngine/Shaders/ShaderProgram.h>

namespace Render::AnomalyEngine::Shaders {
    class ShaderProgram;
}

namespace Render::AnomalyEngine::Components {
    class Mesh;
}

namespace Render::AnomalyEngine {
    class Material {
    friend class Components::Mesh;

    private:
        const Components::Mesh* _parentMesh;

    public:
        std::unique_ptr<Shaders::ShaderProgram> Shader = nullptr;


    private:
        Material(const Components::Mesh* parent);
    public:
        ~Material() = default;

        template<
            typename T,typename = std::enable_if_t<
            std::is_base_of_v<Render::AnomalyEngine::Shaders::ShaderProgram, T>
            >>
        bool InitShader() {
            Shader = std::make_unique<T>(this);
            return true;
        }

    const Components::Mesh *GetParentMesh() const;
    };
}