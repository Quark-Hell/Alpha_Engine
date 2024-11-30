#pragma once
#include <memory>
#include <AnomalyEngine/Shaders/TShaderProgram.h>

#include "AnomalyEngine/Shaders/ShaderProgram.h"

namespace AnomalyEngine {
    class Mesh;
}

namespace AnomalyEngine {
    class Material {
    friend class Mesh;
    friend class RenderEngine;

    private:
        Mesh* _parentMesh;
    public:
        std::unique_ptr<ShaderProgram> Shader = nullptr;

    private:
        Material(Mesh* parent);
    public:
        ~Material() = default;

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<ShaderProgram,T>, bool>>
        T& InitShader() {
            Shader = std::unique_ptr<ShaderProgram>(new T(this));
            return *static_cast<T*>(Shader.get());
        }

        [[nodiscard]] Mesh *GetParentMesh() const;
    };
}