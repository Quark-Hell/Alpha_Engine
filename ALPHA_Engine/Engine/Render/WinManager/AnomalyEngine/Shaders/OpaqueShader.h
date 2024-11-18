#pragma once

#include <array>

#include "ShaderProgram.h"
#include "Render/WinManager/AnomalyEngine/Textures/OpenGLTexture.h"

namespace Render::WindowsManager::AnomalyEngine {
    class OpaqueShader final : public ShaderProgram {
    private:
        /*
        1 - diffuse
        2 - metallic
        3 - specular
        4 - roughness
        5 - anisotropic
        6 - emission
        7 - normal
        8 - opacity
        9 - occlusion
        */
        std::array<OpenGLTexture, 9> _textures;

    public:
        OpaqueShader(Material *parentMat);
        ~OpaqueShader() override = default;

        /*
        Leave the argument empty if you do not want set some texture
        Example: LoadTextures("diffusePath","","","roughnessPath",...);
        */
        void LoadTextures(
            const std::string &diffusePath = "",
            const std::string &metallicPath = "",
            const std::string &specularPath = "",
            const std::string &roughnessPath = "",
            const std::string &anisotropicPath = "",
            const std::string &emissionPath = "",
            const std::string &normalMapPath = "",
            const std::string &opacityMapPath = "",
            const std::string &occlusionMapPath = ""
        );

        bool TransferTexturesToGPU();

        void ApplyShadersSettings(Camera *camera) override;
    };
}
