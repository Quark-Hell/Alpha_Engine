#pragma once
#include <memory>
#include <Render/WinManager/AnomalyEngine/Shaders/ShaderProgram.h>

namespace Render::WindowsManager::AnomalyEngine {
    class ShaderProgram;
    class Mesh;
}

namespace Render::WindowsManager::AnomalyEngine {
    class Material {
    friend class Mesh;

    private:
        Mesh* _parentMesh;

    public:
        std::unique_ptr<ShaderProgram> Shader = nullptr;


    private:
        Material(Mesh* parent);
    public:
        ~Material() = default;

        template<
            typename T,typename = std::enable_if_t<
            std::is_base_of_v<Render::WindowsManager::AnomalyEngine::ShaderProgram, T>
            >>
        bool InitShader() {
            Shader = std::make_unique<T>(this);
            return true;
        }
        [[nodiscard]] Mesh *GetParentMesh() const;
    };
}