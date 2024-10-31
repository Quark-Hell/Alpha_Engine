#pragma once
#include <memory>
#include <Render/WinManager/AnomalyEngine/Shaders/ShaderProgram.h>

namespace AnomalyEngine::Render::Shaders {
    class ShaderProgram;
}

namespace AnomalyEngine::Render::Components {
    class Mesh;
}

namespace AnomalyEngine::Render {
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
            std::is_base_of_v<AnomalyEngine::Render::Shaders::ShaderProgram, T>
            >>
        bool InitShader() {
            Shader = std::make_unique<T>(this);
            return true;
        }

    const Components::Mesh *GetParentMesh() const;
    };
}